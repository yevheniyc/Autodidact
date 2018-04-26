NWD Challenge Solution
======================

The Python application performs the following actions:
------------------------------------------------------
1. Processes records in the nwd-code-challenge-input.csv file.
2. It parses raw_full_name field into a first and last names.
3. It parses the raw_headline into a title and a company name


Scale up methodology
---------------------
1. A few things to consider when working with large datasets:
- don't build large datasets in-memory (like long lists, dicts, tuples)
    - For the 10^6 rows per file, my implementation will use at most ~100 MB.
    It will not cause memory overflow on an average box.
- Python's threads are a bad choice for file processing (especially, if CPU-bound operations
are required), due to the innate GIL lock.
- A better choice for scaling up complex operations would be to use
the `multiprocessing` module. In this case, each input would be processed by
a single process.
2. Below is the example approach (not tested) with the multiprocessing module:
- each process receives a single input_file/output_file combination
- this implementation will proportionally improve the speed based on your box's physical core count
for the use-case when there are 1000s of files with 10^6 lines each. If the process is too slow,
just add CPU power to your EC2s. I've personally had a lot of success with this!

```python
import os
from nwd_challenge_yev import FileParser

def exec_file_parser(input_f, output_f):
    """Each process will start one of these methods"""
    file_parser = FileParser(input_file=input_f, output_file=output_f)
    file_parser.build()

# build a data structure to feed into the "map" method
all_input_output_file_names = []
for index, input_file_name in enumerate(os.listdir(folder_with_files)):
    all_input_output_file_names.append(
        [input_file_name, 'yev-solution-for-{}'.format(input_file_name)])

pool = multiprocessing.Pool()
pool.map(exec_file_parser, all_input_output_file_name)
```

Test Methodology
----------------
1. For this case, I would test for the following features:
- FileParser().split_headline and FileParser().split_full_name should
handle:
    - the easy cases - when names and headlines are easy to split on 'at', ' '
    - more difficult situations
        - when there are multiple 'at' or use of symbols ('@') for company name
        - when there are prefix(es) 'Dr.', or suffix(es) like 'Ph.D.'
        - it would be nice to build up a suite of these unit tests that would
        handle all of these different cases. Or at least a few of the most common ones. 


Python Version:
----------------
Python 3.6

It uses the following modules:
------------------------------
- pandas - `pip install pandas` for working with dataframes
- csv - python module for reading/writing CSV files
- nameparser - `pip install nameparser` for parsing names from non-standard strings


How to Use the module:
----------------------
1. Make sure your environment is properly setup
```bash
# build a virtualenv with Python3 and then
pip install -r requirements.txt
```
2. Enter the root directory of the unzipped file and run the script
```bash
cd nwd_project
python nwd_challenge_yev.py
```
3. The file 'my-solution-2018-03-26' will contain the solved output.
4. Any errors pertaining to the actual parsing will be stored in logs/log.txt
