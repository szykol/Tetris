# Tetris
## Simple 2D Tetris game made with Skeleton and SFML. 

## How to build
### Tetris is based on SFML and Skeleton and uses premake5 to build

Download [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/) and extract it to the *vendor/SFML* folder.

Download [premake5](https://premake.github.io/download.html) and remember it's location or add it to path

### Example: Generating Visual Studio 2019 solution and project files
```
  path/to/premake5.exe vs2019
  // or if the path to SFML is different than default
  path/to/premake5.exe --sfmlpath=path/to/SFML vs2019
```
Then compile it and run with Visual Studio

### Example: Generating Makefiles
```
  path/to/premake5.exe gmake2
  // or if the path to SFML is different than default
  path/to/premake5.exe --sfmlpath=path/to/SFML gmake2
```

After that
```
  make
  // after sucessful compilation
  cd Tetris
  // it needs to be run from the projects root directory for now
  ..\bin\Debug-windows-x86\Tetris\Tetris.exe
```

Keep in mind that path to the downloaded SFML **must be** relative to the premake5.lua script

### Other platforms and project files
For generating other project files or for different platforms head to this [link](https://github.com/premake/premake-core/wiki/Using-Premake)
