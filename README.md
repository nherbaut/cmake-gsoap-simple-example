# DEPENDENCIES #

* c build environment
* gosap
* cmake
* Doxygen

```bash
sudo apt-get build-essentials gsoap libgsoap-dev cmake
```

# COMPILATION #

just launch
```
./create_project_files.sh 
```

that will create makefiles for you in ./build and launch a build. Once created, You can just call make in the build directoty to perform a full build.

# Using ECLIPSE #

You can import project files generated in the build folder in Eclipse CDT. We tried it on eclipse Luna and it may work on other versions.
