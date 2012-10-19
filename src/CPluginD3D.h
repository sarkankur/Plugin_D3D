/* D3D_Plugin - for licensing and copyright see license.txt */

#pragma once

#include <Game.h>

#include <IPluginManager.h>
#include <IPluginBase.h>
#include <CPluginBase.hpp>

#include <IPluginD3D.h>

#define PLUGIN_NAME "D3D"
#define PLUGIN_CONSOLE_PREFIX "[" PLUGIN_NAME " " PLUGIN_TEXT "] " //!< Prefix for Logentries by this plugin

namespace D3DPlugin
{
    /**
    * @brief Provides information and manages the resources of this plugin.
    */
    class CPluginD3D :
        public PluginManager::CPluginBase,
        public IPluginD3D
    {
        private:
            IPluginD3D* m_pDXSystem;

        public:
            CPluginD3D();
            ~CPluginD3D();

            // IPluginBase
            bool Release( bool bForce = false );

            int GetInitializationMode() const
            {
                return int( PluginManager::IM_Default );
            };

            bool Init( SSystemGlobalEnvironment& env, SSystemInitParams& startupParams, IPluginBase* pPluginManager, const char* sPluginDirectory );

            const char* GetVersion() const
            {
                return "1.6.2.0";
            };

            const char* GetName() const
            {
                return PLUGIN_NAME;
            };

            const char* GetCategory() const
            {
                return "Framework";
            };

            const char* ListAuthors() const
            {
                return "Hendrik Polczynski <hendrikpolczyn at gmail dot com>";
            };

            const char* ListCVars() const;

            const char* GetStatus() const;

            const char* GetCurrentConcreteInterfaceVersion() const
            {
                return "1.0";
            };

            void* GetConcreteInterface( const char* sInterfaceVersion )
            {
                return static_cast < IPluginD3D* > ( this );
            };

            // IPluginD3D
            IPluginBase* GetBase()
            {
                return static_cast<IPluginBase*>( this );
            };

            void RegisterListener( ID3DEventListener* item );
            void UnregisterListener( ID3DEventListener* item );

            void* GetDevice();

            void ActivateEventDispatcher( bool bActivate );
            eD3DType GetType();
            void* GetSwapChain();
            void* GetDeviceContext();

            ITexture* CreateTexture( void** pD3DTextureDst, int width, int height, int numMips, ETEX_Format eTF, int flags );
            ITexture* InjectTexture( void* pD3DTextureSrc, int nWidth, int nHeight, ETEX_Format eTF, int flags );
    };

    extern CPluginD3D* gPlugin;
}

/**
* @brief This function is required to use the Autoregister Flownode without modification.
* Include the file "CPluginD3D.h" in front of flownode.
*/
inline void GameWarning( const char* sFormat, ... ) PRINTF_PARAMS( 1, 2 );
inline void GameWarning( const char* sFormat, ... )
{
    va_list ArgList;
    va_start( ArgList, sFormat );
    D3DPlugin::gPlugin->LogV( ILog::eWarningAlways, sFormat, ArgList );
    va_end( ArgList );
};
