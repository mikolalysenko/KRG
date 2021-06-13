#include "AnimationGraphCompiler.h"
#include "Tools/Animation/Graph/AnimationGraphTools_Compilation.h"
#include "Tools/Animation/Graph/AnimationGraphTools_Graph.h"
#include "Tools/Animation/Graph/AnimationGraphTools_AnimationGraph.h"
#include "System/Core/FileSystem/FileSystem.h"
#include "System/Core/Serialization/BinaryArchive.h"
#include "Engine/Animation/Graph/AnimationGraphResources.h"

//-------------------------------------------------------------------------

namespace KRG::Animation
{
    using namespace Graph;

    //-------------------------------------------------------------------------

    AnimationGraphCompiler::AnimationGraphCompiler()
        : Resource::Compiler( "GraphCompiler", s_version )
    {
        m_outputTypes.push_back( AnimationGraphDefinition::GetStaticResourceTypeID() );
        m_outputTypes.push_back( AnimationGraphVariation::GetStaticResourceTypeID() );
        m_virtualTypes.push_back( AnimationGraphDataSet::GetStaticResourceTypeID() );
    }

    Resource::CompilationResult AnimationGraphCompiler::Compile( Resource::CompileContext const& ctx ) const
    {
        auto const resourceTypeID = ctx.m_resourceID.GetResourceTypeID();
        if ( resourceTypeID == AnimationGraphDefinition::GetStaticResourceTypeID() )
        {
            return CompileDefinition( ctx );
        }
        else if ( resourceTypeID == AnimationGraphVariation::GetStaticResourceTypeID() )
        {
            return CompileVariation( ctx );
        }

        KRG_UNREACHABLE_CODE();
        return CompilationFailed( ctx );
    }

    Resource::CompilationResult AnimationGraphCompiler::CompileDefinition( Resource::CompileContext const& ctx ) const
    {
        JsonFileReader jsonReader;
        if ( !jsonReader.ReadFromFile( ctx.m_inputFilePath ) )
        {
            return Error( "Failed to read animation graph file: %s", ctx.m_inputFilePath.c_str() );
        }

        ToolsAnimationGraph toolsGraph;
        if ( !toolsGraph.Load( ctx.m_typeRegistry, jsonReader.GetDocument() ) )
        {
            return Error( "Malformed animation graph file: %s", ctx.m_inputFilePath.c_str() );
        }

        // Compile
        //-------------------------------------------------------------------------

        ToolsGraphCompilationContext context;
        if ( !toolsGraph.Compile( context ) )
        {
            // Dump log
            for ( auto const& logEntry : context.GetLog() )
            {
                if ( logEntry.m_severity == Log::Severity::Error )
                {
                    Error( "%s", logEntry.m_message.c_str() );
                }
                else if ( logEntry.m_severity == Log::Severity::Warning )
                {
                    Warning( "%s", logEntry.m_message.c_str() );
                }
                else if ( logEntry.m_severity == Log::Severity::Message )
                {
                    Message( "%s", logEntry.m_message.c_str() );
                }
            }

            return Resource::CompilationResult::Failure;
        }

        // The last offset is actual the required memory
        context.m_instanceRequiredMemory = context.m_instanceNodeStartOffsets.back();
        context.m_instanceNodeStartOffsets.pop_back();

        // Serialize
        //-------------------------------------------------------------------------

        FileSystem::EnsurePathExists( ctx.m_outputFilePath );
        Serialization::BinaryFileArchive archive( Serialization::Mode::Write, ctx.m_outputFilePath );
        if ( archive.IsValid() )
        {
            archive << Resource::ResourceHeader( s_version, AnimationGraphDefinition::GetStaticResourceTypeID() );
            archive << context;

            // Node settings type descs
            TypeSystem::TypeDescriptorCollection settingsTypeDescriptors;
            for ( auto pSettings : context.m_nodeSettings )
            {
                auto& desc = settingsTypeDescriptors.m_descriptors.emplace_back();
                TypeSystem::Serialization::CreateTypeDescriptorFromNativeType( ctx.m_typeRegistry, pSettings, desc );
            }
            archive << settingsTypeDescriptors;

            // Node settings data
            cereal::BinaryOutputArchive& settingsArchive = *archive.GetOutputArchive();
            for ( auto pSettings : context.m_nodeSettings )
            {
                pSettings->Save( settingsArchive );
            }

            return CompilationSucceeded( ctx );
        }
        else
        {
            return CompilationFailed( ctx );
        }
    }

    Resource::CompilationResult AnimationGraphCompiler::CompileVariation( Resource::CompileContext const& ctx ) const
    {
        AnimationGraphVariationResourceDescriptor resourceDescriptor;
        if ( !ctx.TryReadResourceDescriptor( resourceDescriptor ) )
        {
            return Error( "Failed to read resource descriptor from input file: %s", ctx.m_inputFilePath.c_str() );
        }

        // Load anim graph
        //-------------------------------------------------------------------------

        FileSystem::Path graphFilePath;
        if ( !ctx.ConvertDataPathToFilePath( resourceDescriptor.m_graphDataPath, graphFilePath ) )
        {
            return Error( "invalid graph data path: %s", resourceDescriptor.m_graphDataPath.c_str() );
        }

        JsonFileReader jsonReader;
        if ( !jsonReader.ReadFromFile( graphFilePath ) )
        {
            return Error( "Failed to read animation graph file: %s", ctx.m_inputFilePath.c_str() );
        }

        ToolsAnimationGraph toolsGraph;
        if ( !toolsGraph.Load( ctx.m_typeRegistry, jsonReader.GetDocument() ) )
        {
            return Error( "Malformed animation graph file: %s", ctx.m_inputFilePath.c_str() );
        }

        StringID const variationID = resourceDescriptor.m_variationID.IsValid() ? resourceDescriptor.m_variationID : AnimationGraphVariation::DefaultVariationID;
        if ( !toolsGraph.IsValidVariation( variationID ) )
        {
            return Error( "Invalid variation requested: %s", variationID.c_str() );
        }

        // Compile
        //-------------------------------------------------------------------------
        // We need to compile the graph to get the order of the data slots

        ToolsGraphCompilationContext context;
        if ( !toolsGraph.Compile( context ) )
        {
            // Dump log
            for ( auto const& logEntry : context.GetLog() )
            {
                if ( logEntry.m_severity == Log::Severity::Error )
                {
                    Error( "%s", logEntry.m_message.c_str() );
                }
                else if ( logEntry.m_severity == Log::Severity::Warning )
                {
                    Warning( "%s", logEntry.m_message.c_str() );
                }
                else if ( logEntry.m_severity == Log::Severity::Message )
                {
                    Message( "%s", logEntry.m_message.c_str() );
                }
            }

            return Resource::CompilationResult::Failure;
        }

        // Create requested data set resource
        //-------------------------------------------------------------------------

        String dataSetFileName;
        dataSetFileName.sprintf( "%s_%s.%s", graphFilePath.GetFileNameWithoutExtension().c_str(), variationID.c_str(), AnimationGraphDataSet::GetStaticResourceTypeID().ToString().c_str() );

        FileSystem::Path dataSetFilePath = graphFilePath.GetParentDirectory();
        dataSetFilePath.Append( dataSetFileName );
        DataPath const dataSetDataPath = DataPath::FromFileSystemPath( ctx.m_sourceDataPath, dataSetFilePath );

        if ( !GenerateVirtualDataSetResource( ctx, toolsGraph, context, variationID, dataSetDataPath ) )
        {
            return Error( "Failed to create data set: %s", dataSetDataPath.c_str() );
        }

        // Create variation resource and serialize
        //-------------------------------------------------------------------------

        AnimationGraphVariation variation;
        variation.m_pGraphDefinition = ResourceID( resourceDescriptor.m_graphDataPath );
        variation.m_pDataSet = ResourceID( dataSetDataPath );

        //-------------------------------------------------------------------------

        FileSystem::EnsurePathExists( ctx.m_outputFilePath );
        Serialization::BinaryFileArchive archive( Serialization::Mode::Write, ctx.m_outputFilePath );
        if ( archive.IsValid() )
        {
            Resource::ResourceHeader hdr( s_version, AnimationGraphDataSet::GetStaticResourceTypeID() );
            hdr.AddInstallDependency( variation.m_pDataSet.GetResourceID() );
            hdr.AddInstallDependency( variation.m_pGraphDefinition.GetResourceID() );

            archive << hdr;
            archive << variation;

            return CompilationSucceeded( ctx );
        }
        else
        {
            return CompilationFailed( ctx );
        }
    }

    //-------------------------------------------------------------------------

    bool AnimationGraphCompiler::GenerateVirtualDataSetResource( Resource::CompileContext const& ctx, ToolsAnimationGraph const& toolsGraph, ToolsGraphCompilationContext const& compilationContext, StringID const& variationID, DataPath const& dataSetPath ) const
    {
        AnimationGraphDataSet dataSet;
        dataSet.m_variationID = variationID;

        //-------------------------------------------------------------------------
        // Get skeleton for variation
        //-------------------------------------------------------------------------

        KRG_ASSERT( toolsGraph.IsValidVariation( variationID ) );
        auto const pVariation = toolsGraph.GetVariation( variationID );
        KRG_ASSERT( pVariation != nullptr ); 
        if ( !pVariation->m_pSkeleton.IsValid() )
        {
            Error( "Skeleton not set for variation: %s", variationID.c_str() );
            return false;
        }

        dataSet.m_pSkeleton = pVariation->m_pSkeleton;

        //-------------------------------------------------------------------------
        // Fill data slots
        //-------------------------------------------------------------------------

        THashMap<UUID, DataSlotNode const*> dataSlotLookupMap;
        auto const& dataSlotNodes = toolsGraph.GetAllDataSlotNodes();
        for ( auto pSlotNode : dataSlotNodes )
        {
            dataSlotLookupMap.insert( TPair<UUID, DataSlotNode const*>( pSlotNode->GetID(), pSlotNode ) );
        }

        dataSet.m_resources.reserve( compilationContext.m_registeredDataSlots.size() );

        for ( auto const& dataSlotID : compilationContext.m_registeredDataSlots )
        {
            auto iter = dataSlotLookupMap.find( dataSlotID );
            if ( iter == dataSlotLookupMap.end() )
            {
                Error( "Unknown data slot encountered (%s) when generating data set", dataSlotID.ToString().c_str() );
                return false;
            }

            auto const dataSlotResourceID = iter->second->GetValue( toolsGraph.GetVariations(), variationID );
            dataSet.m_resources.emplace_back( dataSlotResourceID );
        }

        //-------------------------------------------------------------------------
        // Serialize
        //-------------------------------------------------------------------------

        FileSystem::Path const dataSetOutputPath = dataSetPath.ToFileSystemPath( ctx.m_compiledDataPath );
        FileSystem::EnsurePathExists( dataSetOutputPath );
        Serialization::BinaryFileArchive archive( Serialization::Mode::Write, dataSetOutputPath );
        if ( archive.IsValid() )
        {
            Resource::ResourceHeader hdr( s_version, AnimationGraphDataSet::GetStaticResourceTypeID() );

            hdr.AddInstallDependency( dataSet.m_pSkeleton.GetResourceID() );

            for ( auto const& dataRecord : dataSet.m_resources )
            {
                if ( dataRecord.IsValid() )
                {
                    hdr.AddInstallDependency( dataRecord.GetResourceID() );
                }
            }

            archive << hdr << dataSet;
            return true;
        }
        else
        {
            return false;
        }
    }
}
