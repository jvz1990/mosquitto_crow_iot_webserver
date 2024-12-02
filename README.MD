Conan commands to get started:

```
conan profile detect --force
conan install . --output-folder=build --build=missing
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
```
To test, in a separate terminal:
```
mosquitto_sub -h localhost -p 1883 -t example/topic
```