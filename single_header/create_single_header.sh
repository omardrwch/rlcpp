rm -rf single_header/all_files
python single_header/preprocess.py
python single_header/acme.py single_header/all_files/rlcpp.h
mv single_header/all_files/output/rlcpp.h single_header/rlcpp.h
rm -rf single_header/all_files
