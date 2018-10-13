sudo rm -rf ./Simple-Web-Server/build
cd ./webserver/
mkdir build
cd build
cmake ..
make
cd ..
/usr/bin/open -a "/Applications/Google Chrome.app" 'https://2b194e87.ngrok.io/'
./build/http_examples
