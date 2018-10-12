sudo rm -rf ./Simple-Web-Server/build
cd ./Simple-Web-Server/
mkdir build
cd build
cmake ..
make
cd ..
./build/http_examples
