# Matlab Coder Output to Emscripten Project Template

> [WARNING]
> This project may break due to MATLAB and MATLAB Coder updates.

> [WARNING]
> This project contains copied over libraries taken from a live install of MATLAB, hence you are advised to not use this repo commercially. The external libraries and more are kept in the extern/ folder. 

```bash
mkdir -p input output
```

Now copy over the contents of the codegen/lib/genAnalysisLogic/ folder to input/ folder. We assume the project name is genAnalysisLogic, please edit pixi.toml and README.md files to change this.

After that, install pixi with steps from here and run `pixi run export-web` if you just want to compile or `pixi run server` if you want to start a quick web server.
