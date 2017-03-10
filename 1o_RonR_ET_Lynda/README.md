# Ruby on Rails
![alt text](imgs/1_ronr.png "MVC")

### Installing Ruby on Rails on Mac

- PATH setup - **Important to add the eval statement**
```bash
export PATH="/usr/local/bin:/usr/local/sbin:/usr/local/mysql/bin:$PATH"
eval "$(rbenv init -)" # run this comman every time a window is opened
```

- Install Xcode Developers Tools: gcc
```bash
$ gcc -v
$ xcode-select --install 
```

- Install Homebrew
```bash
# get the curl code from Homebrew homepage
$ brew doctor
$ brew update # update packages
```

- Install Ruby: 2.4.0: use RVM or RBENV for managing ruby versions - virtual envs
```bash
$ ruby -v
# Get the Released version
$ brew update
$ brew install rbenv # manages switching between ruby versions
$ brew install ruby-build  # installs ruby - it is installed as a dependency
$ rbenv install --list # list all available ruby version - choose the most recent that is not a preview release
$ rbenv install 2.3.1 # grab and install the package
$ rbenv rehash # every time a new ruby version or gem is installed - makes rbenv aware of all the new/updated commands
$ rbenv versions # check which versions are installed - "*" indicates which version is activated
$ rbenv global 2.3.1 (2.4.0) # will setup ruby version for the user
$ rbenv versions # will activate 2.3.1 version
$ rbenv local 2.3.1 # will setup ruby version for a particular dir
$ rbenv shell 2.3.1 # will change version for the current window
$ rbenv uninstall # blahblah
```

- Install RubyGems: another package manager - ruby helper libraries and packages (rails is a gem)
```bash
$ gem -v
$ gem list # to list all installed gems
$ gem update --system # update gem version
$ gem -v # the newest version should have been installed
```

Visit **rubygems.org** to check all of the available gems and dependencies

- Install Rails gem
```bash
# Make sure to activate proper ruby version
$ rbenv global/local/shell 2.4.0
$ gem install bundler # necessary for managing rails applications
$ sudo gem install nokogiri # a dependency of other tools
# download rails gem + dependencies
$ gem install rails
$ gem list # view all of the installed gems
$ rails -v # rails version -> 5.0.2
```

- Install MySQL | set default pw | Install MySQL RubyGem
```bash
$ brew update
$ brew install mysql
# to run mysql as is
$ mysql.server start
$ mysql -uroot
# to run mysql as a launch deamon
brew services start mysql
# to configure root pw/security
$ mysql_secure_installation # to set a root password
$ mysql -uroot -p # enter the pw

# now isntall rubygem for mysql or postgres
gem install mysql2
gem install pg
```

- Installing Web Server

Production: Apache2 or NGINX
Passenger or Unicorn: are the lighter web servers that help handling requests between rails and the production server.
For development: WEBrick (prev versions) -> Puma (Rails 5) - allows concurrency, can be used in production, **comes with rails**

- Create a new project
```bash
cd ~/Sites
rails new demo_project -d mysql
rails new demo_project_pg -d postgresql # create files + bundle (installs all ruby gems for the app)
# every time a gem is added, run:
bundle install # to update the gems
```

Now, attatch this project to the currently activate ruby version
```bash
cd demo_project
ruby -v
rbenv local 2.3.1 # a new file will appear in the root dir:
# .ruby-version - indicates which ruby version is used by this project

```





