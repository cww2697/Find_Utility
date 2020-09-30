# Find Utility
Concepts of Operating Systems - Programming Project 2

Functions like the Linux/Unix find function.
Currently supports Linux/MacOS.
Windows support comming soon.

To compile code unzip or git pull, and run make from inside the project directory.
All indended functionalities have been implemented and tested for accuracy. 

## Intended functionalities:
* find *where-to-look* 
* find *where-to-look* *criteria*
  * find *where-to-look* -n <specified file name>
  * find *where-to-look* -m <specified number of minutes>
  * find *where-to-look* -i <specified inode number>
* find *where-to-look* *criteria* -r
* find *where-to-look* *criteria* -e <specified unix function>
* find -?
 
## Syntax for functionalities
* find -w *where-to-look* 
* find -w *where-to-look* *criteria*
  * find -w *where-to-look* -n <specified file name>
  * find -w *where-to-look* -m <specified number of minutes>
  * find -w *where-to-look* -i <specified inode number>
* find -w *where-to-look* *criteria* -r
* find -w *where-to-look* *criteria* -e <specified unix function>
  * find -w *where-to-look* *criteria* -e "cat ./path/to/file"
  * find -w *where-to-look* *criteria* -e "rm"
  * find -w *where-to-look* *criteria* -e "mv ./path/to/new/name"
* find -?

## Notes on implemented functionalities:
* **find *where to look*** syntax in the program is implemented as **find -w <*where to look*>**
* Specified number of minutes refers to some _**n**_ number of minutes
  * _**+n**_ should be used to find files modified more than _**n**_ minutes ago
  * _**n**_ should be used to find files modified exactly _**n**_ minutes ago
  * _**-n**_ should be used to find files modified less than _**n**_ minutes ago
  * Uses linux epoch time and will not function correctly if last modified date is prior to 00:00:00 1 January 1970
