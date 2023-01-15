del /f /s /q external
rmdir /s /q external
mkdir external
cd external

git clone https://github.com/Microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat
