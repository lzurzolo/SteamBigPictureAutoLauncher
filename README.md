# SteamBigPictureAutoLauncher

This is a simple application I wrote out of pure laziness. This is a tiny (Windows Only) application that switches your primary display/audio from your monitor to your TV and launches Steam in big picture mode. Upon exiting Steam, it will set your primary display/audio back to your monitor/PC speakers.

There is a simple config.ini file that you use to define your TV and monitor settings. The enclosed INI file should be rather self explanatory. Simply look up your display settings and choose the display ID associated with your monitor and TV. For audio devices, copy the name of the respective audio devices into the ini file. Ensure you also set the Steam path in the INI file.

## Compiling

Should compile in VS2019 with no issues. Ensure you pull the inih submodule. Upon building, copy the included multimonitortool and nircmd directories into the output directory.