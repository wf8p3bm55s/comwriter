Сборка
---
Windows
---
В проекте используется Qt 5.15.0.
Перед сборкой необходимо убедиться, что путь к директории с компилятором указан в System PATH.
В текущем каталоге:

    mkdir build
    cd build
    cmake -S "../" -B "./" -G "CodeBlocks - MinGW Makefiles" -DQt5_DIR:PATH="%PATH_TO_QT%\5.15.0\mingw81_64\lib\cmake\Qt5" -DCMAKE_BUILD_TYPE:STRING="MinSizeRel" -DCMAKE_GNUtoMS:BOOL="0"
    cmake --build . --target all

Исполняемый файл будет находиться в каталоге ./build
Для упрощения развертывания и запуска можно использовать приложение [CQtDeployer](https://github.com/QuasarApp/CQtDeployer)

    cqtdeployer.exe -bin "comwriter.exe" -targetDir "deploy" -qmake "%PATH_TO_QT%\5.15.0\mingw81_64\bin\qmake.exe" noTranslations
