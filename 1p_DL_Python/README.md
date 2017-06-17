# Deep Dive into Python Machine Learning

This repo follows Safaribooksonline's Learning Path: Deep Dive Into Python Machine learning. It consists of the following sections:

1. Chapter 1: Mastering Python
2. Chapter 2: Data Mining with Python: Implementing Classification and Regression
3. Chapter 3: Python Machine Learning Solutions
4. Chapter 4: Deep Learning with Python

---

## Ongoing Review of Important Points:

- Duck-typing: defaultdict(list/string/int/anything)
- Adding a method to class: class Example -> Example.added = function

---

## Chapter 1: Mastering Python

### First-Class Functions and Classes

In Python, Functions and Classes are First-Class Objects: 

- First-Class Object means something is a Data Value and it can be accessed, modified, stored and otherwise manipulated by the program its a part of
- In Python, a function is as much a data value as a text string is
- The same goes for classes - data value in classes means an instance of a class
- Data Structures themselves are data values
- The function is stored in the variable defined in the def statement. This variable is just like any other variable, holding a value. This means that we can use it in expressions, assign this value to other values, or even store a different value in place of the original function
- More importantly (and most of the time) we can add an attribute to the function object. Allowing us to store custom information about a function as part of the function and access that information later
- One common task that the functions make easier is assigning hanlders to events. To bind a hanlder function to an event in python, we just pass the function object as a parameter:

```python
# bar
# <function bar at 0x...>
# bar.__name__
# foo or bar
bar.plugin_name = 'demo'
bar.plugin_name # 'demo'
```

- Classes can be used as parameters to the function calls
- Execute a function before exit, by passing a funciton as an argument to the **atexit** utility/class

```python
import atexit
atexit.register(bar)
# <function foo or bar at 0x...>
```

- Like function definition statements, class definition statements create a class object and store it in the variable. But how can it be: classes define objects, however, they are objects themselves? Just like a blueprint that describes the building, the blueprint itself is something. Therefore, classes can be stored as variables and otherwise treated as Data Values.
- Classes can be used as parameters to the function calls, as in the example with **defaultdict**
  - How does defaultdict know how to create a default value: it knows because we gave it a class as a parameter when we created default dict. Therefore, if we want a dictionary of lists then we can give defaultdict **list** class as it's ("how to make a default") parameter.
  - As a side note, **defaultdict** can accept a function as it's ("how to make a default") parameter.
  - **defaultdict** doesn't really care about which parameter is passes, as long as it gets a value when adding a default value.
- The above set of statements represents **duck typing** - it doesn't matter if the parameter is a function, a class, or anything else, as long as it behaves properly.

Function Object Attributes vs Class Object Attributes:

- Function object attributes are only visible to the function or the code using the function
- Class object attributes are visible to the class, or the instances of that class. We also have a greater ability to manipulate classes than objects:

```python
# Add a function to the class, and then execute that function as one of the class's methods
class Example:
    class_trait = 5
    def __init__(self):
        self.instance_trait = 7
Example
# <class '__main__.Example'>

def new_function(self);
    print(self.instance_trait, self.class_trait)

Example.added = new_function
x = Example()
x.added() # 7 5
Example.class_trait = 9
x.added() # 7 9
```

### Extensive Standard Library

**Collections** - Container datatypes:

- namedtuple()
- deque
- ChainMap
- Counter
- OrderedDict
- defaultdict
- UserDict
- UserList
- UserString

**heapq** - Heap queue algorithm - priority queue structures

**pickle** - Python object serialization:

- Transorms arbitrary python data into a sequence of bytes that can be stored in a file or stored accross the network
- Also has package to transorm the data back from bytes to usable python data

**sqlite3** - interface for SQLite databases

**json** - JSON encoder and decoder: hanldes int, str, null, array and maps them to the proper datatypes

**base64** - Base16, Base32, Base64, Base85 Data Encodings: binary to ASCII encoding/decoding

**html** and **xml**

**urllib** - URL handling modules: - retrieve data or send data from/to URLs

**itertools** and **functools** - Functions creating iterators for efficient looping

- functools - implement partially applied functions
- itertools - allows us to concatenate iterators

**enum** - Create/support named enumerations: each enumerations is a distinct datatype, like a class

**pathlib** - Object-oriented filesystem paths: provides system-independent pathfile system operations

**inspect** - Inspect live objects - gives ability to analyze objects

- Get information about live objects such as modules, classes, methods, functions, tracebacks, frame objects, and code objects.

### New in Python 3.5

- Keywords to define **Coroutins**

```python
5 @ 10 # matrix multiplication
```

```python
values = [1, 2, 3]
def needs_params(a, b, c):
    print(a, b, c)

needs_params(*values) # 1 2 3
partial_values1 = [1, 2]
partical_values2 = [3]
needs_params(*partial_values1, partial_values2) # 1 2 3
combined_values = [*partial_values1, *partial_values2] # flaten list of lists
combined_values # [1, 2, 3]
```

- Other packages included in 3.5

**typing** - type hinting
**zipapp** - manage executable python zip archives (.pyc), especially when distributing the application to the users.

### Setting Up

Python versions:

- Python 2

```python
from urllib import urlopen, URLError

def fetch_email(url):
    try:
        data = urlopen(url).read()
        return data.split('mailto:')[1].split('"')[0]
    except (IndexError, URLError), error:
        print error
        return 'invalid@example.com'
```

- Python 3

```python
from urllib.request import urlopen
from urllib.error impor URLError

def fetch_email(url):
    try:
        data = urlopen(url).read().decode('utf8')
        return data.split('mailto:')[1].split('"')[0]
    except (IndexError, URLError) as error:
        print(error)
        return 'invalid@example.com'
```

### Using pip

Make sure we have permissions to write into the Python's library directory

```bash
# to install into system's python directory
pip install banknumber
# to install into user's python directory
pip install --user requests
# view packages
pip list
# upgrade a specific library
pip install --upgrade requests
# uninstall
pip uninstall requests
```

Finding packages in the Python Package Index

- What if we don't know which library to use for the task? Search in **PyPI.python.org**

```bash
pip search asyncio
```

### Creating Packages

- Create a simple, empty package
- Add code modules to the package
- Accessing code from other modules in the package
- Adding static data files to the package

#### Create a simple, empty package

- How Python recognizes packages
- How to add  metadata to a package
- Import our package, to see it work

```bash
mkdir demopackage
```

Two things turn a folder into a regular package:

- 

