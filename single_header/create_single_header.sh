rm -rf single_header/all_files
python single_header/preprocess.py
python single_header/acme.py single_header/all_files/rlcpp.hpp
mv single_header/all_files/output/rlcpp.hpp single_header/rlcpp.hpp
rm -rf single_header/all_files
