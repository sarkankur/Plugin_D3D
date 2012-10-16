// This sample will make your rendering window green, but you are free
// to do something more meaningfull ;)

#include <IPluginD3D.h>
#include <d3d9.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>

class CMyD3D
    : private ID3DEventListener
{
protected:
	bool bDX9;

	union device    // Declare union type
	{
		void* ptr;
		IDirect3DDevice9*	dx9;
		//ID3D11Device*		dx11;
	} m_pDevice;

	IDirect3DStateBlock9*	m_pStateBlock;

	void OnPrePresent() {
		if(bDX9)
		{
			// Save current D3D State [Optional: if you don't modify it]
			m_pStateBlock->Capture();

			// Apply custom rendering
			// Make window green (TODO: Remove this and add your own stuff)
			//m_pDevice.dx9->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(200,255,0), 1.0f, 0);

			// Restore D3D State for next frame
			m_pStateBlock->Apply();
		}
	};

	void OnPostPresent() {};
	void OnPreReset() {
		SAFE_RELEASE(m_pStateBlock);
	};
	void OnPostReset() {};
	void OnPostBeginScene() {};

public:
	CMyD3D() {
		m_pDevice.ptr	= NULL;
		m_pStateBlock	= NULL;

		if(gD3DSystem)
		{
			// Initialize the device
			m_pDevice.ptr = gD3DSystem->GetDevice();
			bDX9 = true;

			if(bDX9 && m_pDevice.ptr)
			{ // Create D3D State [Optional: if you don't modify it]
				m_pDevice.dx9->CreateStateBlock(D3DSBT_ALL, &m_pStateBlock);
			}

			// the listeners will be called renderer thread.
			gD3DSystem->RegisterListener(this);
		}
	}

	~CMyD3D() {
		if(gD3DSystem)
			gD3DSystem->UnregisterListener(this);

		SAFE_RELEASE(m_pStateBlock);
	}
};
