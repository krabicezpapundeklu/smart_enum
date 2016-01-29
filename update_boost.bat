rmdir boost /q /s
bcp --scan --boost=%BOOST_ROOT% smart_enum.hpp .
