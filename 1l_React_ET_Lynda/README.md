### React Essential Training - Lynda
The example files contain start and finish mini-project that were created while following the tutorials. Below is the tutorial step-by-step description with important commands and scripts

Allow markdown specific code snippets to be added in vim:

```vim
let g:markdown_fenced_languages = ['html', 'vim', 'ruby', 'python', 'bash=sh']
```


#### Chapter 2

##### 1. Let's start with the following

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

##### 2. Now let's use JSX implementation to simplify syntax

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

- When running the app, we will see the error message, indicating that the browser cannot read **HTML** tags this way

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

##### 3. Transpiling HTML -> JS is expensive for the browser. Instead let's transpile before runtime with npm/babel packages

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

##### 4. Automate **httpster** startup
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

##### 5. Automating with **Webpack**

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

##### 6. Load React dependencies and JSON data with webpack
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

##### 7. Server CSS with **webpack**
- Change styling info in **lib.js**
```javascript
// ...
import './stylesheets/goodbye.scss'
import './stylesheets/hello.css'

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

***

#### Chapter 3 - Activity Counter app
Before proceeding, let's make sure we do NOT push all of the npm modules. However, I don't want to install packages globally either. Webpack makes it easy for us, the **npm install --save-dev packages...** command will install all of the packages under **~/node_modules**. 

- So let's execute the following: 
```bash
npm install --save-dev 
				babel-cli 
				json-loader 
				babel-preset-latest 
				babel-preset-react 
				babel-preset-stage-0 
				webpack 
				babel-loader 
				webpack-dev-server 
				style-loader 
				css-loader 
				autoprefixer-loader 
				sass-loader 
				node-sass

npm install --save 
				react 
				react-dom

npm install --save react-icons
```

- Let's adjust **package.json** to accomodate new loacation of the webpack-dev-server
```javascript
// ...
"scripts": {
    "start": "~/node_modules/.bin/webpack-dev-server"
  }
// ...
```
Proper import of the packages (i.e. react, react-dom, etc.) should be hanlded by **npm**

- Let's make sure our **webpack.config.js** is consistant with the dir structure
```javascript
var webpack = require("webpack");

module.exports = {
	entry: "./src/index.js",
	output: {
		path: "dist/assets",
		filename: "bundle.js",
		publicPath: "assets"
	},
	devServer: {
		inline: true,
		contentBase: './dist',
		port: 3000
	},
	module: {
		loaders: [
			{
				test: /\.js$/,
				exclude: /(node_modules)/,
				loader: ["babel-loader"],
				query: {
					presets: ["latest", "stage-0", "react"]
				}
			},
			{
				test: /\.json$/,
				exclude: /(node_modules)/,
				loader: "json-loader"
			},
			{
				test: /\.css$/,
				loader: 'style-loader!css-loader!autoprefixer-loader'
			},
			{
				test: /\.scss$/,
				loader: 'style-loader!css-loader!autoprefixer-loader!sass-loader'
			}
		]
	}
}
```

- Now **cd** into the appropriate dir and start webpack
```bash
# same dir as package.json
npm start
```

##### 1. Build apps based on components with React

- Create **SkiDayCount** component
```bash
mkdir src/components
touch src/components/SkiDayCount.js
```

```javascript
// src/components/SkiDayCount.js
import React from 'react'
import '../stylesheets/ui.scss'

// export the class so that to make it visible for imports from other files
export const SkiDayCount = React.createClass({
    render() {
        return (
            <div className="ski-day-count">
                <div className="total-days">
                    <span>5 days</span>
                </div>
                <div className="powder-days">
                    <span>2 days</span>
                </div>
                <div className="backcountry-days">
                    <span>1 hicking day</span>
                </div>
            </div>
        )
    }
})
```

- Now, let's add the new component to the dom
```javascript
// src/index.js
import React from 'react'
import { render } from 'react-dom'
import {SkiDayCount} from './components/SkiDayCount'

window.React = React // sometimes an error: React is not defined shows up, this will resolve it

render(
	<SkiDayCount />,
	document.getElementById('react-container')
)
```

##### 2. With slight modification we can incorporate variables throught our classes/components
```javascript
// src/index.js
import React from 'react'
import { render } from 'react-dom'
import { SkiDayCount } from './components/SkiDayCount'

window.React = React

render(
	<SkiDayCount total={50}
				 powder={20}
				 backcountry={10}
				 goal={100}/>,
	document.getElementById('react-container')
)
```

```javascript
// src/components/SkiDayCount.js
import React from 'react'
import '../stylesheets/ui.scss'

export const SkiDayCount = React.createClass({
	render() {
		return (
			<div className="ski-day-count">
				<div className="total-days">
					<span>{this.props.total}</span>
				</div>
				<div className="powder-days">
					<span>{this.props.powder}</span>
				</div>
				<div className="backcountry-days">
					<span>{this.props.backcountry}</span>
				</div>
			</div>
		)
	}
})
```

##### 3. Adding methods to the components
- Keeping most of the forementioned the same, add methods to classes/components
```javascript
// src/components/SkiDayCount.js
import React from 'react'
import '../stylesheets/ui.scss'

export const SkiDayCount = React.createClass({
	percentToDecimal(decimal) {
		// decimal to percent
		return ((decimal * 100) + '%')
	},
	calcGoalProgress(total, goal) {
		// get the progress
		return this.percentToDecimal(total/goal)
	},
	render() {
		// call methods with {this.calcGoalProgress(params)}
		return (
			<div className="ski-day-count">
				<div className="total-days">
					<span>{this.props.total}</span>
					<span>days</span>
				</div>
				<div className="powder-days">
					<span>{this.props.powder}</span>
					<span>days</span>
				</div>
				<div className="backcountry-days">
					<span>{this.props.backcountry}</span>
					<span>days</span>
				</div>
				<div>
					<span>
						{this.calcGoalProgress(
							this.props.total,
							this.props.goal
						)}
					</span>
				</div>
			</div>
		)
	}
})
```

##### 4. ES6 **class syntax**
- ES6 (ECMAScript 6) describes how JS should be implemented by browsers. One feature of ES6 that is often used with React is **class syntax**. React has a base class called **React.Component**, and we then extend this class to create our own components.

- Let's refractor our SkiDayCount components as ES6 class
```javascript
import {Component} from 'react' 			// import specific components
import '../stylesheets/ui.scss'

export class SkiDayCount extends Component { // slightly different syntax
	percentToDecimal(decimal) {
		return ((decimal * 100) + '%')
	} 										// remove comas from methods
	calcGoalProgress(total, goal) {
		return this.percentToDecimal(total/goal)
	}
	render() {
		return (
			<div className="ski-day-count">
				<div className="total-days">
					<span>{this.props.total}</span>
					<span>days</span>
				</div>
				<div className="powder-days">
					<span>{this.props.powder}</span>
					<span>days</span>
				</div>
				<div className="backcountry-days">
					<span>{this.props.backcountry}</span>
					<span>days</span>
				</div>
				<div>
					<span>
						{this.calcGoalProgress(
							this.props.total,
							this.props.goal
						)}
					</span>
				</div>
			</div>
		)
	}
}
```

##### 5. An alternative to creating components with **createClass** and **ES6 class** is by a function.

**Stateless functional components**:

- are functions that take in property information and return JSX elements.
- can't access **this**, so properties are passed directly into the function
- local methods must be removed and put into their own functions:
```javascript
const MyComponent = (props) => (
	<div>{props.title}</div>
)
```
- Stateless functional components is another great approach and might have speed advantages over **React.Components**
```javascript
// SkiDayCount.js

// 1. Remove React.Components
// 2. Remove class, render, this syntax
import '../stylesheets/ui.scss'

const percentToDecimal = (decimal) => {
	return ((decimal * 100) + '%')
}

const calcGoalProgress = (total, goal) => {
	return percentToDecimal(total/goal)
}

export const SkiDayCount = ({total, powder, backcountry, goal}) => (
	<div className="ski-day-count">
		<div className="total-days">
			<span>{total}</span>
			<span>days</span>
		</div>
		<div className="powder-days">
			<span>{powder}</span>
			<span>days</span>
		</div>
		<div className="backcountry-days">
			<span>{backcountry}</span>
			<span>days</span>
		</div>
		<div>
			<span>
				{calcGoalProgress(
					total, 
					goal
				)}
			</span>
		</div>
	</div>
)
```

##### 6. Adding React-icons
```bash
npm install --save react-icons
```
***

#### Chapter 4 - Props and State
Start building multiple components in React

##### 1. Build a table
- Let's pass **JSON** object into the table component (SkiDayList)
```javascript
import React from 'react'
import { render } from 'react-dom'
import { SkiDayList } from './components/SkiDayList'

window.React = React

render(
	<SkiDayList days={
		[
			{
				resort: "Squaw Valley",
				date: new Date("1/2/2016"),
				powder: true,
				backcountry: false
			},
			{
				resort: "Kirkwood",
				date: new Date("3/28/2016"),
				powder: false,
				backcountry: false
			},
			{
				resort: "Mt. Tallac",
				date: new Date("4/2/2016"),
				powder: false,
				backcountry: true
			}
		]
	}/>,
	document.getElementById('react-container')
)
```

- Next, let's build the actual **SkiDayList** component
```javascript
import Terrain from 'react-icons/lib/md/terrain'
import SnowFlake from 'react-icons/lib/ti/weather-snow'
import Calendar from 'react-icons/lib/fa/calendar'
import {SkiDayRow} from './SkiDayRow'

export const SkiDayList = ({days}) => (
	// Loop through each item in days object and apply it to <SkiDayRow/>
	// You can also use an optional spread operator {...day} to access each object
		// days.map( (day, i) => <SkiDayRow key={i} {...day}}/> )
    <table>
        <thead>
            <tr>
                <th>Date</th>
                <th>Resort</th>
                <th>Powder</th>
                <th>Backcountry</th>
            </tr>
        </thead>
        <tbody>
            {days.map((day, i) =>
                <SkiDayRow key={i}
                            resort={day.resort}
                            date={day.date}
                            powder={day.powder}
                            backcountry={day.backcountry}/>
            )}
        </tbody>
    </table>
)
```

- Next, build each row in the table **SkiDayRow** and pass variables
```javascript
import Terrain from 'react-icons/lib/md/terrain'
import SnowFlake from 'react-icons/lib/ti/weather-snow'
import Calendar from 'react-icons/lib/fa/calendar'

export const SkiDayRow = ({resort, date, 
                            powder, backcountry}) => (
    <tr>
        <td>
            {date.getMonth() + 1}/{date.getDate()}/{date.getFullYear()}
        </td>
        <td>
            {resort}
        </td>
        <td>
            {(powder) ? <SnowFlake/> : null}
        </td>
        <td>
            {(backcountry) ? <Terrain/> : null}
        </td>
    </tr>
)
```

##### 2. Set default props
- Using **createClass** approach
```javascript
export const SkiDayCount = createClass({
	// use getDefaultProps method for providing default values
	getDefaultProps() {
		return {
			total: 50,
			powder: 50,
			backcountry: 15,
			goal: 100
		}
	},
	percentToDecimal(decimal) {
		return ((decimal * 100) + '%')
	},
	calcGoalProgress(total, goal) {
		return this.percentToDecimal(total/goal)
	},
	render() {
		return (
			<div className="ski-day-count">
			...
			</div>
		)
	}
})
```

- Using **ES6 class** approach
```javascript
export class SkiDayCount extends Component {
  // same as before ...
}

// To ad default properties
SkiDayCount.defaultProps = {
  total: 50,
  powder: 50,
  backcountry: 15,
  goal: 100
}
```

- Using Stateless way
```javascript
// Either add defaults in the arguments with {total=70} or
// with SkiDayCount.defaultProps method
// ... imports
// ... functions

export const SkiDayCount = ({total=70, powder=20, 
							backcountry=10, goal=100}) => (
	// ...
)

SkiDayCount.defaultProps = {
	total: 50,
	powder: 50,
	backcountry: 15,
	goal: 100
}
```

##### 3. Validating with **React.PropTypes**
**PropTypes** allow us to supply a property type for all of our different properties, so that it will validate to make sure that we're supplying the right type. In this way prop types are both a feature and working documentation about the properties that you are using, and what should be supplied as values.

- Using **createClass** approach
```javascript
export const SkiDayCount = createClass({
	propTypes: {
		total: PropTypes.number.isRequired, // must be supplied
		powder: PropTypes.number,
		backcountry: PropTypes.number
	}
})
```

- Using **ES6 class** apprach, as well as stateless
```javascript
import {..., PropTypes} from 'react'
// ... all the same and at the buttom
SkiDayCount.propTypes = {
	total: PropTypes.number,
	powder: PropTypes.number,
	backcountry: PropTypes.number
}
```

##### 4. Custom Validation
- Let's build a custom validations for the incoming data
```javascript
// SkiDayList.js
SkiDayList.PropTypes = {
	days: PropTypes.array
}

// or

SkiDayList.propTypes = {
	days: function(props) {
		if(!Array.isArray(props.days)) { // not array
			return new Error(
				"SkiDayList should be an array"
			)
		} else if(!props.days.length) { // empty array
			return new Error(
				"SkiDayList must have at least one record"
			)
		} else {						// everything is fine!
			return null
		}
	}
}
```

##### 5. Working with States
State represents the possible conditions for your application. Maybe you have a state for editing, a state for saved, a state for logged in or logged out. In React apps we want to identify the minimal representation of app state, and then we want to reduce state to as few components as possible. This way we can avoid overwriting state variables, which can cause chaos in our applications.

```javascript
// index.js
// ... imports
import { App } from './components/App'
// ... other stuff
render(
	<App />,
	document.getElementById('react-container')
)
```

```javascript
// App.js
import {createClass} from 'react'

export const App = createClass({
    // getInitialState in a createClass component is how we initialize state as the default.
    // So when our app renders for the first time, we will use this initial state.
    // So instead of using data as props, we will use it as state!
    getInitialState() {
        return {
            allSkiDays: [
                {
                    resort: "Squaw Valley",
                    date: new Date("1/2/2016"),
                    powder: true,
                    backcountry: false
                },
                {
                    resort: "Kirkwood",
                    date: new Date("3/28/2016"),
                    powder: false,
                    backcountry: false
                },
                {
                    resort: "Mt. Tallac",
                    date: new Date("4/2/2016"),
                    powder: false,
                    backcountry: true
                }
            ]
        }
    },
    render() {
        return (
            <div className="app">
                {this.state.allSkiDays[0]["resort"]}
            </div>
        )
    }
})
```

In the next part, we will pass this data down from parent to children

##### 6. Passing **state** as **props**
- Now let's pass **state** or various parts of **state** to children
```javascript
import { createClass } from 'react'
import {SkiDayList} from './SkiDayList'
import {SkiDayCount} from './SkiDayCount'

export const App = createClass({
	getInitialState() {
		return {
			allSkiDays: [
			{
				resort: "Squaw Valley",
				date: new Date("1/2/2016"),
				powder: true,
				backcountry: false
			},
			{
				resort: "Kirkwood",
				date: new Date("3/28/2016"),
				powder: false,
				backcountry: false
			},
			{
				resort: "Mt. Tallac",
				date: new Date("4/2/2016"),
				powder: false,
				backcountry: true
			}
		]
		}
	},
	countDays(filter) {
		const {allSkiDays} = this.state
		return allSkiDays.filter((day) => 
			(filter) ? day[filter] : day).length
	},
	render() {
		// Pass the entire JSON to SkiDayList component
		// Pass filtered JSON to SkiDayCount component
		return (
			<div className="app">
				<SkiDayList days={this.state.allSkiDays}/>
				<SkiDayCount total={this.countDays()}
							 powder={this.countDays(
								 "powder"
							 )}
							 backcountry={this.countDays(
								 "backcountry"
							 )}/>
			</div>
		)
	}
})
```

##### 7. Create stateful components with ES6
- The ES6 method for making the **state** available to the methods
```javascript
// ... the same

export class App extends Component {
	// The constructor initiation ensures that this.state is excesible inside methods
	constructor (props) {
		super(props)		// call the super class and pass props to it
		this.state = {
				allSkiDays: [
				// ... the same
			]
		}
	}
	// ... the same
}
```

***

#### Chapter 5 - React Router
Display different screens using the **React Router**

##### 1. Incorporating the Router
- Install **React-Router**
```bash
npm install -save react-router
```

- Incorporate the router
```javascript
//index.js
import React from 'react'
import { render } from 'react-dom'
import './stylesheets/ui.scss'
import { App } from './components/App'
import {Whoops404} from './components/Whoops404'
// Router - for all of the separate routes
// hashHistory
import {Router, Route, hashHistory} from 'react-router'

window.React = React

render(
	// "/" -> will render our app's home page
	// "*" -> any other url will be routed to the 404 page
	// history={hashHistory} 
		// - listen to the browser's address bar for any changes, and
			// it will keep track of those things
		// - we use it here without a need to configure a server
	<Router>
		<Router path="/" component={App}/>
		<Router path="*" component={Whoops404}/>
	</Router>,
	document.getElementById('react-container')
)
```

```javascript
// Whoops404.js
// we don't need brackets when rendering only JSX components
export const Whoops404 = () =>
    <div>
        <h1>Whoops, route not found</h1>
    </div>
```

##### 2. Setting up routes
```javascript
// index.js
// ...
render(
	<Router history={hashHistory}>
		<Route path="/" component={App}/>
		<Route path="list-days" component={App} />
		<Route path="add-day" component={App} />
		<Route path="*" component={Whoops404}/>
	</Router>,
	document.getElementById('react-container')
)
```

```javascript
// App.js
// ...
render() {
		return (
			<div className="app">
			{
				// if route path is "/" -> trigger SkiDayCount component
				// if route path is "/add-day" -> AddDayForm
				// if route path is "SkiDayList" -> SkiDayList
				(this.props.location.pathname === "/") ?
					<SkiDayCount total={this.countDays()}
									powder={this.countDays(
											"powder"
										)}
									backcountry={this.countDays(
											"backcountry"
										)}/> :
				(this.props.location.pathname === "/add-day") ? 
					<AddDayForm /> :
					<SkiDayList days={this.state.allSkiDays}/>
			}	
			</div>
		)
	}
```

##### 3. Navigating with the link component
Well, the **Link** component is just **<a href=""></a>** elements

```javascript
// index.js
// ...
render(
	<Router history={hashHistory}>
		<Route path="/" component={App}/>
		<Route path="list-days" component={App} />
		<Route path="add-day" component={App} />
		<Route path="*" component={Whoops404}/>
	</Router>,
	document.getElementById('react-container')
)
```

```javascript
// Menu.js
// ... imports
export const Menu = () =>
    <nav classMenu="menu">
        <Link to="/" activeClassName="selected">
            <HomeIcon />
        </Link>
        <Link to="/add-day" activeClassName="selected">
            <AddDayIcon/>
        </Link>
        <Link to="/list-days" activeClassName="selected">
            <ListDaysIcon />
        </Link>
    </nav>
// end
```

```javascript
// App.js
// ... imports
export class App extends Component {
	constructor(props) {
		super(props)
		this.state = {
			allSkiDays: [
				// JSON
			]
		}
	}
	// ... methods
	render() {
		return (
			// Build the page with the components
			<div className="app">
				<Menu />
				{(this.props.location.pathname === "/") ?
					<SkiDayCount total={this.countDays()}
									powder={this.countDays(
											"powder"
										)}
									backcountry={this.countDays(
											"backcountry"
										)}/> :
				(this.props.location.pathname === "/add-day") ?
					<AddDayForm /> :
					<SkiDayList days={this.state.allSkiDays}/>				 
				}
					
			</div>
		)
	}
}
```

##### Using Route Parameters
If I want to pass additional parameters via the urls, follow the structure below

```javascript
// index.js
// ... imports
render(
	// Add another route with the ":filter" path
	<Router history={hashHistory}>
		<Route path="/" component={App}/>
		<Route path="list-days" component={App}> 
			<Route path=":filter" component={App} />
		</Route>
		<Route path="add-day" component={App} />
		<Route path="*" component={Whoops404}/>
	</Router>,
	document.getElementById('react-container')
)
```

```javascript
// App.js
import { Component } from 'react'
import { SkiDayList } from './SkiDayList'
import { SkiDayCount } from './SkiDayCount'
import { AddDayForm } from './AddDayForm'
import { Menu } from './Menu'

export class App extends Component {
	constructor(props) {
		super(props)
		this.state = {
			allSkiDays:
			// JSON
		}
	}
	// ...
	render() {
		// Pass filter paramter entered in the url
		return (
			<div className="app">
			<Menu />
			{(this.props.location.pathname === "/") ?
			  <SkiDayCount total={this.countDays()}
							 powder={this.countDays(
							 		"powder"
							 	)}
							 backcountry={this.countDays(
							 		"backcountry"
							 	)}/> :
			 (this.props.location.pathname === "/add-day") ?
			 	<AddDayForm /> :
			 	<SkiDayList days={this.state.allSkiDays}
				 			filter={this.props.params.filter}/>				 
			}
					
			</div>
		)
	}
}
```

```javascript
// SkiDayList.js
// ... imports

export const SkiDayList = ({days, filter}) => {
	// if 
		// there is no filter or
		// filter does not match /powder or /backountry
			// then return days
		// otherwise
			// return day[filter] - filtered days
	const filteredDays = (!filter ||
		!filter.match(/powder|backcountry/)) ?
		days :
		days.filter(day => day[filter])

	return (
		<div className="ski-day-list">
			<table>
				<thead>
					<tr>
						<th>Date</th>
						<th>Resort</th>
						<th>Powder</th>
						<th>Backcountry</th>
					</tr>
					<tr>
						<td colSpan={4}>
							<Link to="/list-days">
								All days
							</Link>
							<Link to="/list-days/powder">
								Powder Days
							</Link>
							<Link to="/list-days/backcountry">
								Back Country
							</Link>
						</td>
					</tr>
				</thead>
				<tbody>
					{filteredDays.map((day, i) =>
						<SkiDayRow key={i}
								{...day}/>	
						)}
				</tbody>

			</table>
		</div>
	)
}
```

##### Nesting routes
- Let's install all of the dependenices indicated in **package.json**
```javascript
{
	"name": "react-router-demo",
	"version": "0.0.1",
	"description": "A React Router tutorial.",
	"main": "index.js",
	"scripts": {
		"prestart": "node_modules/.bin/webpack",
		"start": "node_modules/.bin/webpack-dev-server"
  },
	"author": "Eve Porcello <eve@moonhighway.com>",
	"license": "MIT",
	"devDependencies": {
		"babel-cli": "^6.18.0",
		"babel-loader": "^6.2.7",
		"babel-preset-latest": "^6.16.0",
		"babel-preset-react": "^6.16.0",
		"babel-preset-stage-0": "^6.16.0",
		"webpack": "^1.13.3",
		"webpack-dev-server": "^1.16.2"
  },
	"dependencies": {
		"isomorphic-fetch": "^2.2.1",
		"react": "^15.3.2",
		"react-dom": "^15.3.2",
		"react-icons": "^2.2.1",
		"react-router": "^3.0.0"
  }
}
```

```javascript
// index.js
import React from 'react'
import { render } from 'react-dom'
import routes from './routes'

window.React = React

render(routes, document.getElementById('react-container'))
```

```javascript
// components/index.js
import MainMenu from './ui/MainMenu'

export const Left = ({children}) => 
    <div className="page">
        <MainMenu className="main-menu" />
        {children}
    </div>

export const Right = ({children}) => 
    <div className="page">
        {children}
        <MainMenu className="main-menu" />
    </div>

export const Whoops404 = ({ location }) =>
    <div>
        <h1>Whoops, resource not found</h1>
        <p>Could not find {location.pathname}</p>
    </div>
```

```javascript
// routes.js
import React from 'react'
import { Router, Route, hashHistory } from 'react-router'
import Home from './components/ui/Home'
import About from './components/ui/About'
import MemberList from './components/ui/MemberList'
import  { Whoops404  } from './components'

const routes = (
    <Router history={hashHistory}>
        <Route path="/" component={Home} />
        <Route path="/" component={Right}>
            <Route path="about" component={About} />
            <Route path="members" component={MemberList} />
        </Route>
        <Route path="*" component={Whoops404} />
    </Router>
)

export default routes
```

```javascript
import { Link } from 'react-router'
import FaHome from 'react-icons/lib/fa/home'

const MainMenu = () => {
    return (
        <nav>
            <Link to="/"><FaHome/></Link>
            <Link to="about" 
            	  activeStyle={{
            	  backgroundColor: "white", 
            	  color: "slategray"
            	}}>
            	About
            </Link>
            <Link to="members" 
            	  activeStyle={{
            	  	backgroundColor: "white", 
            	  	color: "slategray"
            	  }}>
            	  Members
           	</Link>
        </nav>
    )
}

export default MainMenu
```

```javascript
import MainMenu from './MainMenu'

const Home = () =>
    <div className="home">
        <MainMenu className="home-page-menu"/>
        <div id="homebox">
            <h1>Rock Appreciation Society</h1>
        </div>
    </div>

export default Home
```

***

#### Chapter 6 - Forms and Refs

##### 1. Creating a from component

```javascript
// index.js
render(
	<Router history={hashHistory}>
		<Route path="/" component={App}/>
		<Route path="list-days" component={App}>
			<Route path=":filter" component={App} />
		</Route>
		<Route path="add-day" component={App} />
		<Route path="*" component={Whoops404}/>
	</Router>,
	document.getElementById('react-container')
)
```

```javascript
// App.js
// ... imports
import { Component } from 'react'
import { SkiDayList } from './SkiDayList'
import { SkiDayCount } from './SkiDayCount'
import { AddDayForm } from './AddDayForm'
import { Menu } from './Menu'

export class App extends Component {
	constructor(props) {
		super(props)
		this.state = {
			allSkiDays: [
			// JSOn
			]
		}
	}
	// methods
	render() {
		return (
			<div className="app">
			<Menu />
			{(this.props.location.pathname === "/") ?
			  <SkiDayCount total={this.countDays()}
							 powder={this.countDays(
							 		"powder"
							 	)}
							 backcountry={this.countDays(
							 		"backcountry"
							 	)}/> :
			 (this.props.location.pathname === "/add-day") ?
			 	<AddDayForm /> :
			 	<SkiDayList days={this.state.allSkiDays}
			 				filter={this.props.params.filter}/>				 
			}
					
			</div>
		)
	}
}
```

```javascript
// AddDayForm.js
import { PropTypes, Component } from 'react'

export class AddDayForm extends Component {
	render() {
		const {resort, date, powder, backcountry} = this.props
		return (
			<form className="add-day-form">
				<label htmlFor="resort" >Resort Name</label>
				<input id="resort" 
						type="text" 
						required
						defaultValue={resort} />

				<label htmlFor="date" >Date</label>
				<input id="date" 
						type="date" 
						required
						defaultValue={date} />

				<div>
					<input id="powder" 
							type="checkbox" 
							defaultChecked={powder} />
					<label htmlFor="powder" >Powder Day</label>
				</div>

				<div>
					<input id="backcountry" 
							type="checkbox" 
							defaultChecked={backcountry} />
					<label htmlFor="backcountry" >Backcountry</label>
				</div>
			</form>
		)
	}
}

AddDayForm.defaultProps = {
	resort: "Kirkwood",
	date: "2017-02-12",
	powder: true,
	backcountry: false
}

AddDayForm.propTypes = {
	resort: PropTypes.string.isRequired,
	date: PropTypes.string.isRequired,
	powder: PropTypes.bool.isRequired,
	backcountry: PropTypes.bool.isRequired
}
```

##### 2. Using Refs in class components
Use **refs** for sumitting form data

```javascript
// index.js
// ... same as above
```

```javascript
// App.js
// ... same as above
```

```javascript
import { PropTypes, Component } from 'react'

export class AddDayForm extends Component {

	constructor(props) {
		super(props)
		// not sure if necessary, but helps to see all of the methods up top!
		this.submit = this.submit.bind(this);
	}
	submit(e) {
			e.preventDefault()
			consolge.log('resort', this.refs.resort.value)
			consolge.log('date', this.refs.date.value)
			consolge.log('powder', this.refs.powder.checked)
			consolge.log('backcountry', this.refs.backcountry.checked)
	}
	render() {
		const { resort, date, powder, backcountry } = this.props 

		return (
			// include the onSubmit action
			<form onSubmit={this.submit} className="add-day-form">

				<label htmlFor="resort">Resort Name</label>
				<input id="resort" 
					   type="text" 
					   required 
					   defaultValue={resort}
					   ref="resort"/>

				<label htmlFor="date">Date</label>
				<input id="date" 
					   type="date" 
					   required 
					   defaultValue={date}
					   ref="date"/>

				<div>
					<input id="powder" 
						   type="checkbox" 
						   defaultChecked={powder}
						   ref="powder"/>
					<label htmlFor="powder">Powder Day</label>
				</div>

				<div>	
					<input id="backcountry" 
						   type="checkbox"
						   defaultChecked={backcountry} 
						   ref="backcountry"/>
					<label htmlFor="backcountry">
						Backcountry Day
					</label>
				</div>
				<button>Add Day</button>
			</form>
		)
	}
}

AddDayForm.defaultProps = {
	resort: "Kirkwood",
	date: "2017-02-12",
	powder: true,
	backcountry: false
}

AddDayForm.propTypes = {
	resort: PropTypes.string.isRequired,
	date: PropTypes.string.isRequired,
	powder: PropTypes.bool.isRequired,
	backcountry: PropTypes.bool.isRequired
}
```

##### 3. Using Refs in stateless functional components
- Need to change things a bit, as the sateless components don't contain state == this
```javascript
import { PropTypes, Component } from 'react'

export const AddDayForm = ({ resort, date, powder, backcountry }) => {
	
	// keep these variables in scope
	let _resort, _date, _powder, _backcountry
	
	const submit = (e) => {
		e.preventDefault()
		console.log('resort', _resort.value)
		console.log('date', _date.value)
		console.log('powder', _powder.checked)
		console.log('backcountry', _backcountry.checked)

	}

	return (
		<form onSubmit={submit} className="add-day-form">

			<label htmlFor="resort">Resort Name</label>
			<input id="resort" 
					type="text" 
					required 
					defaultValue={resort}
					ref={input => _resort = input}/>

			<label htmlFor="date">Date</label>
			<input id="date" 
					type="date" 
					required 
					defaultValue={date}
					ref={input => _date = input}/>

			<div>
				<input id="powder" 
						type="checkbox" 
						defaultChecked={powder}	
						ref={input => _powder = input}/>
				<label htmlFor="powder">Powder Day</label>
			</div>

			<div>	
				<input id="backcountry" 
						type="checkbox"
						defaultChecked={backcountry} 
						ref={input => _backcountry = input}/>
				<label htmlFor="backcountry">
					Backcountry Day
				</label>
			</div>
			<button>Add Day</button>
		</form>
	)
}

// ... same defaultProps and propTypes
```

#### 4. Two-way function binding
Now that we have access to the form values we need to pass them up the component tree to the parent, the **App.js**

The following is **beautiful**: 

- First *define** (addDay) and **bind** (this.addDay = ...) the method to the **App** constructor. Then pass the method to **AddDayForm**
```javascript
// ... imports
export class App extends Component {
	// here is the constractor if defined state and method
	constructor(props) {
		super(props)
		this.state = {
			allSkiDays: [
			{
				resort: "Squaw Valley",
				date: "2016-01-02",
				powder: true,
				backcountry: false
			}
		]
		}
		this.addDay = this.addDay.bind(this)
	}

	addDay(newDay) {
	// this will be passed to AddDayForm child as a callback
	// once the callback is triggered with the new day data,
	// it will update the App's state
		this.setState({
			allSkiDays: [
				// ES6 spread operator: take all of the existing days that are held in state, 
				// it will going to push those into a new state object, and will also add the newDay
				...this.state.allSkiDays,
				newDay
			]
		})
	}

	// ... other methods

	render() {
		return (
			// ... everythign the same
			<AddDayForm onNewDay={this.addDay}/>
		)
	}
}
```

- In the **AddDayForm** component pass the callback, and trigger with the new day data
```javascript
import { PropTypes} from 'react'

export const AddDayForm = ({ resort, 
							 date, 
							 powder, 
							 backcountry,
							 onNewDay }) => {
	
	let _resort, _date, _powder, _backcountry
	
	const submit = (e) => {
		e.preventDefault()
		// this is just a callback function passed from App.js == this.addDay
		// It is triggered here once the parameters are passed
		onNewDay({
			resort: _resort.value,
			date: _date.value,
			powder: _powder.checked,
			backcountry: _backcountry.checked
		})
		// once the form is submitted, let's reset our values to empty stings
		_resort.value = ''
		_date.value = ''
		_powder.checked = false
		_backcountry.checked = false

	}

	return (
		// same form info
		<form onSubmit={submit} className="add-day-form">
		</form>
	)
}
```

#### 5. Adding an autocomplete component
Add autocomplete component

```javascript
import { PropTypes, Component } from 'react'

const tahoeResorts = [
	"Alpine Meadows",
	"Boreal",
	"Diamond Peak",
	"Donner Ski Ranch", 
	"Heavenly", 
	"Homewood",
	"Kirkwood",
	"Mt. Rose", 
	"Northstar",
	"Squaw Valley",
	"Sugar Bowl"
]

// we will create the Autocomplete component in the same place
class Autocomplete extends Component {
	// getter and setter in ES6 classes - this is a standard to retrive
	// and set the value on search
	get value() {
		return this.refs.inputResort.value
	}

	set value(input) {
		this.refs.inputResort.value = inputValue
	}

	render() {
		return (
			<div>
				<input ref="inputResort" 
						type="text" 
						list="tahoe-resorts" />
				<datalist id="tahoe-resorts">
					{this.props.options.map(
						(opt, i) => <option key={i}>{opt}</option>
					)}
				</datalist>
			</div>
		)
	}
}

export const AddDayForm = ({ resort, 
							 date, 
							 powder, 
							 backcountry,
							 onNewDay }) => {
	
	// same let and const

	return (
		<form onSubmit={submit} className="add-day-form">

			<label htmlFor="resort">Resort Name</label>
			<Autocomplete options={tahoeResorts}
				   ref={input => _resort = input}/>
		</form>
	)
}

// same defaultProps and PropTypes
```

***

#### Chapter 7 - Understanding Component Lifecycle
React provides methods that you can use to execute bits of code at certain moments in a component's lifetime. 

##### 1. Understanding the mounting cycle
- Grab some data from **https://api.randomuser.me/?nat=US&results=12**
- The **loading** state variable is initially set to false, and will be trigerred to **true** with another method
- **import 'isomorphic-fetch'** to load data from API; it is included in the **npm install json**

```javascript
import { Component } from 'react'
import fetch from 'isomorphic-fetch' // loading the data from API!
import Member from './Member'

class MemberList extends Component {

    constructor(props) {
        super(props)
        this.state = {
            members: [],
            loading: false // set as false when the render is staring
        }
    }

    // will fire as soon the as the render method fires for the first time
    componentDidMount() {
        this.setState({loading: true})
        fetch('https://api.randomuser.me/?nat=US&results=12')
            // once we receive a response from the API, we will turn it into json
            // function(response) {
                // return response.json()
            // } -> same as below
            .then(response => response.json())
            // let's pass the return parameter (response.json() as json into the next function)
            .then(json => json.results)
            // take results to set the state
            .then(members => this.setState({
                members, // same as members = members -> ES6 literal enhancement
                loading: false
            }))
    }

    render() {
		// set local scope
			// if loading is true, then show the below component
			// if any of the members are returned:
				// loop through each one of them with "map" (could also filter)
					// and parse the needed information
    	const { members, loading } = this.state
        return (
            <div className="member-list">
                <h1>Society Members</h1>
			
                { 
                    (loading) ? 
                    <span>laoding...</span> :
                    <span>{members.length} members</span>
                }
                { 
                    (members.length) ? 
                        members.map(
                            (member, i) => 
                                <Member key={i} 
                                        name={member.name.first + ' ' + member.name.last}
                                        email={member.email}
                                        thumbnail={member.picture.thumbnail}/>
                        ):
                        <span>Currently 0 Members </span>
                }
            </div>
        )
    }
}

export default MemberList
```

##### 2. Understanding updating cycle







