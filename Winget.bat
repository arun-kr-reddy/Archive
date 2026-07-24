@echo off

REM ============================ Internet ============================
winget install -e --id Google.Chrome
winget install -e --id=TorProject.TorBrowser
winget install -e --id=qBittorrent.qBittorrent

REM ============================ Utilities ============================
winget install -e --id=7zip.7zip
winget install -e --id=TheDocumentFoundation.LibreOffice
winget install -e --id Flow-Launcher.Flow-Launcher
winget install -e --id=xanderfrangos.twinkletray
winget install -e --id Microsoft.WindowsTerminal
winget install MusicBee

REM ============================ Coding ============================
winget install -e --id Microsoft.VisualStudioCode
winget install -e --id Git.Git
winget install -e --id DEVCOM.JetBrainsMonoNerdFont
winget install -e --id WinMerge.WinMerge

REM ============================ Media ============================
winget install -e --id=mpv.net
winget install -e --id=HandBrake.HandBrake
winget install -e --id=MoritzBunkus.MKVToolNix
winget install -e --id=MediaArea.MediaInfo.GUI
winget install -e --id jely2002.youtube-dl-gui

REM ============================ Gaming & Hardware ============================
winget install -e --id=Valve.Steam
winget install -e --id=RazerInc.RazerInstaller.Synapse4

REM ============================ Windows Settings ============================
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Search" /v BingSearchEnabled /t REG_DWORD /d 0 /f
reg add "HKCU\Software\Classes\CLSID\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\InprocServer32" /f /ve

pause

REM ============================ Archive ============================
REM https://winstall.app/
REM winget install -e --id=Microsoft.VisualStudio.Community
REM "C:\Program Files (x86)\Microsoft Visual Studio\Installer\setup.exe" modify --installPath "C:\Program Files\Microsoft Visual Studio\18\Community" --add Microsoft.VisualStudio.Workload.NativeDesktop --includeRecommended
REM winget install -e --id=Nvidia.CUDA