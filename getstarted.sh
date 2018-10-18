sudo rm -rf ./Simple-Web-Server/build
cd ./webserver/
mkdir build
cd build
cmake ..
make
cd ..
/Applications/Google\ Chrome.app/Contents/MacOS/Google\ Chrome --app='https://2b194e87.ngrok.io/'
./build/http_examples
