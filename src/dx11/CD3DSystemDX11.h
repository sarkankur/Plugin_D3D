/* D3D_Plugin - for licensing and copyright see license.txt */

#pragma once

#include <IPluginD3D.h>

namespace D3DPlugin
{
    class CD3DSystem11 :
	    public IPluginD3D, private ID3DEventListener
    {
    private:
	    bool m_bD3DHookInstalled;
	    std::vector<ID3DEventListener*> vecQueue;
	    CD3DSystem11();
	    void hookD3D(bool bHook);
	    ~CD3DSystem11();

    public:
	    int m_nTextureMode;
	    void* m_pTempTex;
	    void* m_pDevice;
	    void* m_pDeviceCtx;
	    void* m_pSwapChain;

	    static CD3DSystem11* initSingleton();

        PluginManager::IPluginBase* GetBase() { return NULL; };

	    void ActivateEventDispatcher(bool bActivate) { hookD3D(bActivate); };

	    void RegisterListener(ID3DEventListener* item);
	    void UnregisterListener(ID3DEventListener* item);
	    void* GetDevice();
	    eD3DType GetType() {return m_pDevice ? D3D_DX11 : D3D_NONE;};
	    void* GetSwapChain() {return NULL;}; // DX11 only
	    void* GetDeviceContext() {return NULL;}; // DX11 only

	    ITexture* CreateTexture(void** pD3DTextureDst, int width, int height, int numMips, ETEX_Format eTF, int flags);
	    ITexture* InjectTexture(void* pD3DTextureSrc, int nWidth, int nHeight, ETEX_Format eTF, int flags);

    public:
    #define BROADCAST_EVENT(METHOD) \
	    void METHOD() { \
	    for(std::vector<ID3DEventListener*>::const_iterator	iterQueue = vecQueue.begin(); iterQueue!=vecQueue.end(); ++iterQueue) \
	    (*iterQueue)->METHOD(); \
	      }

	    BROADCAST_EVENT(OnPrePresent);
	    BROADCAST_EVENT(OnPostPresent);
	    BROADCAST_EVENT(OnPreReset);
	    BROADCAST_EVENT(OnPostReset);
	    BROADCAST_EVENT(OnPostBeginScene);
    };

    extern CD3DSystem11* gD3DSystem11;
};