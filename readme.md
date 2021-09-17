# A simple project to prettify commit messages

Commit messages are good. They provide information about tons of things. But far
too many commit messages lack emojis! This is a critical problem, and one that I
 will not stand for.

Catify solves this issue. In order to use catify, build and itstall it:

```bash
./build.sh
./install.sh
```
This will place catify in `~/.local/git-hooks/prepare-commit-message`. Then,
whenever you'd like to use catify, simply add

```bash
git config core.hooksPath "$HOME/.local/git-hooks"
```
In whichever repository you'd like to catify!

You can also enable it globally by running:

```bash
git config --global core.hooksPath "$HOME/.local/git-hooks"
```
And you're done!

![Catify Example](/catify.png)

## Reasons to use catify

There are a number of reasons you'd like to use catify, but I've provided a small sampling of them below. 

- Using emojis in commits is neat
- It adds whimsy to an otherwise monotonous task
- It encourages better support for unicode
- Gnome terminal now supports emojis, so your commit messages will display properly
- And finally...

Catify is fast. *Really fast*. Catify processes a 8.8 MB commit message in 27.28ms on my laptop with an underpowered mobile CPU. I'm not sure why you'd have a commit message that long, but what I'm saying is: it adds no noticable delay to commiting. 

Also, catify ignores empty lines and lines starting with `#`, just like git does.

```
alecto@styx:catify$ ll test.txt && perf stat bin/catify test.txt
-rw-r--r-- 1 alecto alecto 8888920 Sep 17 00:58 test.txt

 Performance counter stats for 'bin/catify test.txt':

             26.86 msec task-clock:u              #    0.985 CPUs utilized          
                 0      context-switches:u        #    0.000 /sec                   
                 0      cpu-migrations:u          #    0.000 /sec                   
             2,291      page-faults:u             #   85.296 K/sec                  
        30,187,626      cycles:u                  #    1.124 GHz                    
        50,218,105      instructions:u            #    1.66  insn per cycle         
        11,751,713      branches:u                #  437.528 M/sec                  
            43,690      branch-misses:u           #    0.37% of all branches        

       0.027281482 seconds time elapsed

       0.013702000 seconds user
       0.013630000 seconds sys

```
