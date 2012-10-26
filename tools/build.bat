call "%VS100COMNTOOLS%..\..\VC\vcvarsall.bat" x86

MSBuild "../project/D3D.vcxproj" /t:Rebuild /p:Configuration=Release

call "%VS100COMNTOOLS%..\..\VC\vcvarsall.bat" x64

MSBuild "../project/D3D.vcxproj" /t:Rebuild /p:Configuration=Release
