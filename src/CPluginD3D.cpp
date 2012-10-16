/* D3D_Plugin - for licensing and copyright see license.txt */

#include <StdAfx.h>
#include <CPluginD3D.h>

#include "dx9/CD3DSystemDX9.h"
#include "dx11/CD3DSystemDX11.h"

namespace D3DPlugin
{
    CPluginD3D* gPlugin = NULL;

    CPluginD3D::CPluginD3D()
    {
        gPlugin = this;
    }

    CPluginD3D::~CPluginD3D()
    {
        gPlugin = NULL;
    }

    bool CPluginD3D::Release( bool bForce )
    {
        // Should be called while Game is still active otherwise there might be leaks/problems
        bool bRet = CPluginBase::Release( bForce );

        if ( bRet )
        {
            // Depending on your plugin you might not want to unregister anything
            // if the System is quitting.
            // if(gEnv && gEnv->pSystem && !gEnv->pSystem->IsQuitting()) {

            // Unregister CVars
            if ( gEnv && gEnv->pConsole )
            {
                // ...
            }

            // Unregister game objects
            if ( gEnv && gEnv->pGameFramework )
            {
                // ...
            }

            // Cleanup like this always (since the class is static its cleaned up when the dll is unloaded)
            gPluginManager->UnloadPlugin( GetName() );

            // Allow Plugin Manager garbage collector to unload this plugin
            AllowDllUnload();
        }

        return bRet;
    };

    bool CPluginD3D::Init( SSystemGlobalEnvironment& env, SSystemInitParams& startupParams, IPluginBase* pPluginManager, const char* sPluginDirectory )
    {
        gPluginManager = ( PluginManager::IPluginManager* )pPluginManager->GetConcreteInterface( NULL );
        CPluginBase::Init( env, startupParams, pPluginManager, sPluginDirectory );

        // Register CVars/Commands
        if ( gEnv && gEnv->pConsole )
        {
            // TODO: Register CVARs/Commands here if you have some
            // ...
        }

        // Register Game Objects
        if ( gEnv && gEnv->pGameFramework )
        {
            // TODO: Register Game Objects here if you have some
            // ...
        }

        m_pDXSystem = NULL;
        INT_PTR nModuleOffset = 0;

        if(GetModuleHandle("d3d11.dll") && gEnv->pRenderer->GetRenderType() == eRT_DX11)
        {
            m_pDXSystem = CD3DSystem11::initSingleton();
        }
        else if(GetModuleHandle("d3d9.dll") && gEnv->pRenderer->GetRenderType() == eRT_DX9)
        {
            m_pDXSystem = CD3DSystem9::initSingleton();
        }

        if(!m_pDXSystem)
            gPlugin->LogError("Couldn't find any suitable renderer");

        return true;
    }

    const char* CPluginD3D::ListCVars() const
    {
        return "..."; // TODO: Enter CVARs/Commands here if you have some
    }

    const char* CPluginD3D::GetStatus() const
    {
        return "OK";
    }

    void* CPluginD3D::GetDevice()
    {
        return !m_pDXSystem ? NULL : m_pDXSystem->GetDevice();
    }

    void CPluginD3D::ActivateEventDispatcher(bool bActivate)
    {
        if(m_pDXSystem)
            m_pDXSystem->ActivateEventDispatcher(bActivate);
    }

    eD3DType CPluginD3D::GetType()
    {
        return !m_pDXSystem ? D3D_NONE : m_pDXSystem->GetType();
    }

    void* CPluginD3D::GetSwapChain()
    {
        return !m_pDXSystem ? NULL : m_pDXSystem->GetSwapChain();
    }

    void* CPluginD3D::GetDeviceContext()
    {
        return !m_pDXSystem ? NULL : m_pDXSystem->GetDeviceContext();
    }

    void CPluginD3D::RegisterListener(ID3DEventListener* item)
    {
        if(m_pDXSystem)
            m_pDXSystem->RegisterListener(item);
    }

    void CPluginD3D::UnregisterListener(ID3DEventListener* item)
    {
        if(m_pDXSystem)
            m_pDXSystem->UnregisterListener(item);
    }

    ITexture* CPluginD3D::CreateTexture(void** pD3DTextureDst, int width, int height, int numMips, ETEX_Format eTF, int flags)
    {
        return !m_pDXSystem ? NULL : m_pDXSystem->CreateTexture(pD3DTextureDst, width, height, numMips, eTF, flags);
    }

    ITexture* CPluginD3D::InjectTexture(void* pD3DTextureSrc, int nWidth, int nHeight, ETEX_Format eTF, int flags)
    {
        return !m_pDXSystem ? NULL : m_pDXSystem->InjectTexture(pD3DTextureSrc, nWidth, nHeight, eTF, flags);
    }
}