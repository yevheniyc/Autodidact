### React Essential Training - Lynda
The example files contain start and finish mini-project that were created while following the tutorials. Below is the tutorial step-by-step description with important commands and scripts

Allow markdown specific code snippets to be added in vim:

```vim
let g:markdown_fenced_languages = ['html', 'vim', 'ruby', 'python', 'bash=sh']
```


##### Chapter 2
1. Let's start with the following

```html
<script src="https://fb.me/react-15.1.0.js"></script>
<script src="https://fb.me/react-dom-15.1.0.js"></script>
<body>
    <div id="react-container"></div>
</body>
```

```javascript
const { createElement } = React
const { render } = ReactDOM

// Create html elements with react
const title = createElement(
	'h1',
	{id: 'title', className: 'header'},
	'Hello World'
)

// render html elemnts with react
render(
	title,
	document.getElementById('react-container')
)
```

- To execute the above code we need to setup an HTTP server

```bash
# this will install ./node_modlues/httpster + dependencies
npm install httpster
# to start the server either indicate the executable path or add the path to env
./node_modules/httpster/bin/httpster -d ./dist -p 3000
```

2. Now let's use JSX implementation to simplify syntax

```javascript
const { render } = ReactDOM

render(
	<h1 id='title'
		className='header'
		style={{backgroundColor: 'orange', color: 'white', fontFamily: 'verdana'}}>
	Hello World	
	</h1>,
	document.getElementById('react-container')
)
```
- When running the app, we will see the error message, indicating that the browser cannot
read **HTML** tags this way

- Using the following approach **Babel** transpiles HTML into React syntax **in the browser**

```html
<script src="https://fb.me/react-15.1.0.js"></script>
<script src="https://fb.me/react-dom-15.1.0.js"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/babel-core/5.8.38/browser.js"></script>
</head>
<body>
    <div id="react-container"></div>
    <script type="text/babel" src="index.js"></script>
</body>
```

```javascript
const { render } = ReactDOM

render(
	<h1 id='title'
		className='header'
		style={{backgroundColor: 'orange', color: 'white', fontFamily: 'verdana'}}>
	Hello World	
	</h1>,
	document.getElementById('react-container')
)
```
- The code will run and display the html properly
- React debugger will show a properly rendered and transpiled **index.js**

3. Transpiling HTML -> JS is expensive for the browser. Instead let's transpile before runtime with npm/babel packages
- Build npm packages
- Install Babel cli
```bash
npm init # follow the prompts to create a new package with package.json
# now intall babel cli
npm install --save-dev babel-cli
# or install globaly (not recommended)
sudo npm install -g babel-cli
```

- Move the files around to acquire the following file structure
```bash
$ tree -L 1 start/
start/
├── dist 			# all of the html files
├── node_modules    # in this case all fo the babel dependecies
├── package.json    # after npm init this file indicates package contents
└── src             # our .js files
|- .babelrc         # add this file with the below contents
```

- Edit **.babelrc** file
```javascript
# add presets:
# - supporting all latest ECMAScript features (15-16-17)
# - including react and JSX
{
	'presents': ['latest', 'react', 'stage-0']
}
```

- Install all of the Babel presents
```bash
npm install --save-dev
	babel-preset-latest
	babel-preset-react
	babel-preset-stage-0
```

- Now transpile index.js to bundle.js - make sure to change HTML
```html
<script src="https://fb.me/react-15.1.0.js"></script>
<script src="https://fb.me/react-dom-15.1.0.js"></script></script>
<body>
    <div id="react-container"></div>
    <script type="text/javascript" src="bundle.js"></script>
</body>
```

```bash
# ../node_modlues/.bin/babel -> ../babel-cli/bin/babel.js
babel index.js --out-file bundle.js
```

**Hint**: Try to keep node_modules in a single place for projects

4. Automate **httpster** startup
```json
{
  "name": "react-essential",
  "version": "1.0.0",
  "description": "A project focusing on React and related tools",
  "main": "index.js",
  "scripts": {
    "start": "~/node_modules/httpster/bin/httpster -d ./dist -p 3000"
  },
  "author": "Yev Chu",
  "license": "MIT",
  "devDependencies": {
    "babel-cli": "^6.18.0",
    "babel-preset-latest": "^6.16.0",
    "babel-preset-react": "^6.16.0",
    "babel-preset-stage-0": "^6.16.0"
  }
}
```

Alright, now the transpiling process (converting HTML syntax into JSX) is happening serverside!

5. Automating with **Webpack**
- Is a module bundler that creates static files and automatates processes that need to happen before our app goes to production.
- Webpack will bundle many **script.js** files into a single **bundle.js**, elimnating the need for multiple HTTP request

In order to use **webpack**: 
- Create a **webpack.config.js** file - which describes everything we want to do to our files to ready them for production
```javascript
// webpack.config.js
var webpack = require("webpack");

module.exports = {
    // entry point == the file where it all begins
    entry: "./src/index.js",
    // specify the assets files and the bundled output location
    output: {
        path: "dist/assets",    // path where all of the bundled assets files will reside
        filename: "bundle.js",  // the output filename
        publicPath: "assets"    // folder name where all of the bundled files will reside
    },
    // another important feature when working with webpack is to setup a devServer, which
    // works similary to httpster, however, it allows for hot reloads
    devServer: {
        inline: true,
        contentBase: '/.dist', // where the files are located
        port: 3000
    },
    module: {
        // specify loaders - different tasks that we want webpack to perform
        loaders: [
            { // the first step of the task we are going to setup is the Babel loader
                // 1. Look at all of the files that have .js extension
                test: /\.js$/,              
                // 2. Exclude anything that we don't want Babel to touch
                exclude: /(node_modules)/,
                // 3. The name of the loader to use
                loader: ['babel-loader'],
                // 4. Just like in .babelrc file, specify presets we will use
                query: {
                    presets: ["latest", "react", "stage-0"]
                }
            }
        ]
    }
}
```

- We will need to install a few npm packages
```bash
# if installing locally, make sure to install all of babel dependencies
$ npm install --save-dev 
					babel-preset-latest 
					babel-preset-react 
					babel-preset-stage-0
# install all of the packages as dev dependecies (--save-dev)
npm install --save-dev 
					webpack 
					babel-loader 
					webpack-dev-server
```

- Make sure to src the correct folder in index.html
```html
<div id="react-container"></div>
<script type="text/javascript" src="assets/bundle.js"></script>
```

- Change from **httpster** to **webpack-dev-server** in package.json, which allows for hot reloads
```javascript
// switch to webpack-dev-server
"scripts": {
	"start": "./node_modlues/.bin/webpack-dev-server"
}
```

- Start **webpack**
```bash
./node_modules/.bin/webpack
```

- Start the sever
```bash
npm start # in package.json
```

6. Load React dependencies and JSON data with webpack
- Install React dependencies and remove src import from index.html
```bash
npm install --save react react-dom
```
- You don't need the links in **index.html** anymore
```html
<body>
    <div id="react-container"></div>
    <script type="text/javascript" src="assets/bundle.js"></script>
</body>
```

- Create **titles.json** file
```javascript
{
    "hello": "Bonjour!",
    "goodbye": "Au Revoir"
}
```

- Create **lib.js** to work with JSON data
```javascript
import React from 'react'
import text from './titles.json'

export const hello = (
    <h1 id='title'
        className='header'
        style={{backgroundColor: 'purple', color: 'yellow'}}>
        {text.hello}
    </h1>
)

export const goodbye = (
    <h1 id='title'
        className='header'
        style={{backgroundColor: 'yellow', color: 'purple'}}>
        {text.goodbye}
    </h1>
)
```

- Render the exported variables in index.js
```javascript
import React from 'react'
import {render} from 'react-dom'
import {hello, goodbye} from './lib'

render(
	<div>
		{hello}
		{goodbye}
	</div>,
	document.getElementById('react-container')
)
```

- Change **webpack.config.js** to include **json-loader** module
```javascript
// ...
{
	test: /\.json$/,
	exclude: /(node_modlues)/,
	loader: "json-loader"
}
// ...
```

- Now install the **json-loader**
```bash
npm install --save-dev json-loader
```

**NOTE**: make sure to include previous downloads, if working from a local **node_modules**
```bash
# install babel dependencies
npm install --save-dev babel-cli

# if installing locally, make sure to install all of babel dependencies
npm install --save-dev 
					babel-preset-latest 
					babel-preset-react 
					babel-preset-stage-0

# install all of the packages as dev dependecies (--save-dev)
npm install --save-dev 
					webpack 
					babel-loader 
					webpack-dev-server
```

7. Server CSS with **webpack**
- Change styling info in **lib.js**
```javascript
// ...
import './stylesheets/goodbye.scss'
import './stylesheets/hello.css

export const hello = (
    <h1 id='title'
        className='header'
        style='style'>
        {text.hello}
    </h1>
)

export const goodbye = (
    <h1 id='title'
        className='header'
        style='hello'>
        {text.goodbye}
    </h1>
)
```

- Create a new folder: src/stylesheets
```css
/* hello.css */
.hello {
	background-color: indigo;
	color: turquoise;
}
```
```css
/* goodbye.scss */
$bg-color: turquoise;
$text-color: indigo;

.goodbye {
	background-color: $bg-color;
	color: $text-color;
}
```

- Change a few things in **webpack.config.js**
```javascript
// Add a few more loaders to transpile css/scss into css
// ...
{
	test: /\.css$/,
	loader: 'style-loader!css-loader!autoprefixer-loader'
},
{
	test: /\.scss$/,
	loader: 'style-loader!css-loader!autoprefixer-loader!sass-loader'
}
// ...
```

- Install a few things to be able to bundle/transpile CSS/SCSS
```bash
npm install --save-dev
				style-loader
				css-loader
				autoprefixer-loader
				sass-loader
				node-sass 	# don't forget this package
```

