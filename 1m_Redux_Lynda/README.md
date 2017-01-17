# Learning Redux - Lynda
Redux is a JavaScript library that you can use to manage client data within your application. 
- **Redux** is based on **Flux**, a design pattern that provides developers with an alternative to MVC. It was designed to tackle the challenge of understanding how data changes flow through an application. Using Redux, you can incorporate simplified approaches to data management within your client application that should make it easier to understand, easier to wrap your head around, and ultimately, easier to debug.

This simplified approach is highly dependent on Flux and the functional programming paradigm. 
- This course starts out by defining functional programming and Flux, as well as showing how they've influenced the development of Redux. 
- Once we understand where Redux came from and why we need it, we'll begin working on the client data layer for a small application. 
- This course will be wrapped up by integrating the Redux store into a view layer made of React components.

 The JavaScript community and React community are using the latest features of the JavaScript language so we will too. If you've never seen or used 
 - Arrow functions
 - Object Literal Enhancements
 - Object De-structuring
 - Spread operator
 ...then you might want to brush up on your JavaScript syntax skills by taking Up and Running with ECMAScript 6 with Eve Porcello.

### Chapter 1. What is Redux
In Flux, the data flows in one direction. 

**Action -> Dispatcher -> Store -> View <- User -> ...-> Action**
- Changes are initiated with actions. 
- Actions are objects that describe what should change about the data. 
- Actions are dispatched with the dispatcher. 
- The dispatcher is an object that sends the action to the appropriate store. 
- The store holds the data. It's like a model, but they're not exactly the same. 
- The store is responsible for updating or changing its data.
- Finally, when the store updates the data, that change updates the view. The screen changes, reflecting the data back to the user.
- Now, if the user interacts with the view, a new action is generated and the process starts all over again. Data flows in one direction. 
- Now, as a Flux application grows, it may include more stores and more views, but the dataflow remains unidirectional. All changes in a Flux application begin by dispatching actions and end with updating views. 
- Flux itself is not a library, it's a design pattern that can be implemented with Javascript.

The Facebook Flux library only includes a generic dispatcher that you can use in your Flux applications. So, the community got to work, and GitHub exploded with Javascript libraries that represent variations of this design pattern. Each of these libraries represent a different implementation of Flux. We have Flummox, Alt, Reflux, Fluxxer, McFly, there are too many to name. Redux is one of these Flux implementations. Now, due to its simplicity and ease of use, it has emerged as one of the winners in the Flux library shakedown.

- Redux can help you build applications that are easier to understand. 
- Now, this will make it easier to collaborate with other developers about your codebase and the dataflow in your application. 
- It should also make it easier for you to find and fix bugs.

##### 2. How Redux works
Redux isn't exactly Flux, it's Flux-like. 
- Flux data flows in one direction. An action is sent to the dispatcher, and then dispatched to one or more stores before the view is updated.
- In Redux data still flows in one direction, but there's a big difference. There's only one store. With Redux you cannot use multiple stores, and because there is only one store, there's no need for a dispatcher. The store will dispatch the actions directly. Having one stores means that all of your state will be located in one place. We refer to this as the **single source of truth**.

For example, let's say we have a social media application. All of the data for one client can be stored in a single object. Everything we need to know about the current state of our application is right here. 

```Javascript
{
    user: {
        name: "blah blah",
        email: "blah@gmail.com",
        preferences: {}
    },
    posts: [
        { ... },
        { ... },
        { ... },
    ],
    friends: [
        { ... },
        { ... },
        { ... }
    ],
    errors: []
}
```
We have user information, along with their preferences, information about posts, friends, and we even have an array to save information about errors that could have occurred. Storing everything in one place makes it much easier to reason about the data within our application, and since we have all of the data here, it should make it a little easier for us to track down bugs too.

Now at this point you may be thinking that we lose modularity by storing all of the data in one object. One object does not sound very modular. But with Redux, modularity is obtained through functions. Instead of breaking the state up into different objects, we will create functions that are designed to manage specific leaves and branches of this state tree. We'll have a function to:
- manage the user part
- manage an individual post
- manage an entire array of posts
- We could probably reuse the user function to manage our friends
- we may have a friends function to manage the entire array of friends.
- And we would even have an error function to manage the array of errors.

Functional programming:
- **Pure functions** are functions that do not cause side effects. Everything the function needs to operate is sent as arguments, and a new result is returned. Pure functions do not change any of their arguments or any global variables. They simply use the information to produce a new result.
- **Immutability** -  To mutate is to change, so to be immutable is to be unchangeable. We do not want to change the variables and objects in a functional application. Instead we want to produce new ones. 
- **Composition** refers to the ability to put functions together in a way that one function's output becomes the next function's input. This means that the values returned from one function become the arguments of the next function, until eventually the last function returns the value we were looking for. 

Example of Composition:
getPercent():
    convertToDecimal()
    decimalToPercent()
    addPercentSign()

This is the idea behind composition:

```javascript
import {compose} from 'redux'

const getPercent = compose (
    addPercentSign,
    decimalToPercent,
    convertToDecimal
)

getPercent(1, 4) // 25%
```
- In Redux, composition is used in the store. 

**Action -> reducer/reducer/reducer -> View - Action**

The reducer functions that we create to manage specific parts of the state tree are composed, and the action and state is sent to and piped through each of these reducers until a state is eventually mutated. Now we don't have to worry about how these reducers are composed. All we have to do is identify state, write good reducers, and let the Redux store handle the rest.


##### 3. Plan a Redux app
Use Redux to build the data store that manages all of this state. To start a Redux application start with identifying all of your actions. 
- Form - use will need to ADD_DAY
- List - REMOVE_DAY from the List components
- Goal progress indicator - user need to be able to SET_GOAL
- ADD_ERROR / CLEAR_ERROR
- FETCH_RESORT_NAMES/CANCEL_FETCHING - when we send a request to the server, we want to add an indicator that will let our user know that the request is currently open and we have not received a response. Both actions will control the indicator
- CHANGE_SUGGESTIONS/CLEAR_SUGGESTIONS - use should be able to change the suggestions once we have a resposne, or clear chose suggestions.


**First**, Actions Examples: [1_actions_example.png]

Once we identified all of the Actions needed for this applicaiton, we need to record them in a file called **constants**.

```javascript
// src/constants.js
const constants = {
    ADD_DAY: "ADD_DAY",
    REMOVE_DAY: "REMOVE_DAY",
    SET_GOAL: "SET_GOAL",
    ADD_ERROR: "ADD_ERROR",
    CLEAR_ERROR: "CLEAR_ERROR",
    FETCH_RESORT_NAMES: "FETCH_RESORT_NAMES",
    CANCEL_FETCHING: "CANCEL_FETCHING",
    CHANGE_SUGGESTIONS: "CHANGE_SUGGESTIONS",
    CLEAR_SUGGESTIONS: "CLEAR_SUGGESTIONS"
}

export default constants
```

**Second**, Now that we have identified the actions, we want to identify the variables that those actions impact - **State**

State:
- **allSkiDays** -> []
- **skiDay** -> {resort, date, powder, backcountry}
- **goal** -> number
- **errors** -> []
- **resortNames.fetching** - boolean
- **resortNames.suggestions** - []

 So looking at our wire frames and thinking about our actions, we know that we have ski days. So our main data point is going to be an array. It's going to be an array of objects that contain information about a ski day. So we'll have a date, the resort name, billions for powder or back country. So we can define whether those days are powder days or back country days.

We're also going to have a goal. That can be a number saved in state, and then we'll also need an array for errors. So if any errors occur, we want to display those to the user, and allow the user to clear them from that array. Finally, we need something to control our resort name suggestions. So when we make a request for resort names from the server, we need to set a fetching bullion to true, so that we know that we're making that request, and when we get suggestions from the server, we will need to store those in an array as well. 

**Third**, create an initial state file
The initial state JSON file is found inside of the exercise folder in the source folder right next to constants. This file is designed to be a **snapshot of the state at any given time**. Let's add some data:

```javascript
{
    "allSkiDays": [
        {
            "resort": "Kirwood",
            "date": "2016-12-7",
            "powder": true,
            "backcountry": true

        },
        ...
    ],
    "goal": 10,
    "errors": [],
    "resortNames": {
        // is the file being fetched
        "fetching": false,
        "suggestions": ["SquawValley", "Snobird", "Stowe", "Steamboat"]
    }
}
```

**Next**, we will create **reducers** that will help us to manage data found in the above state tree.

### Chapter 2 - Understanding Reducers
Now, once you have Node.js installed, we'll be ready to start. Now, additionally, we want to use the latest JavaScript syntax that is available to us. But at the same time, we also want to make sure that our JavaScript can run in as many different environments as possible. These including the browser and earlier versions of Node.js. In order to meet both of these requirements, we will use Babel to transpile our source code into ES5-compatible JavaScript. That means that we can use import export statements, object spread, along with other emerging syntax in our source code, right now, today.

```bash
npm init # generate a package.JSON
npm install babel-cli --save-dev # install babel, babel-cli, and save to the package.JSON
# we also need to install presents i.e. - latest features of ES6
npm install babel-preset-latest --save-dev
# we also want to install all of the experimental features
npm install babel-preset-stage-0 --save-dev
```

We also need to create **.babelc** file to tell babel which presets to use:

```javascript
// .babelrc
{
    "presets": ["latest", "stage-0"]
}
```

Create **index.js**:

```javascript
import C from './constants'
import {allSkiDays, goal} from './initialState.json'

// ES6 multiline string
console.log(`
    Ski Day Counter
    ==============
    The goal is ${goal} days
    Initially there are ${allSkiDays.length} ski days in state

    Constants (actions)
    ------------------
    ${Object.keys(C).join('\n    ')}
`)
```

To run the files that include the new syntax, we will need to use **babel-node** command. To do so, open up the **package.json** file and ad the following script:

```javascript
{
 "name" ...
 ....
 "scripts": {
     "start": "./node_modules/.bin/babel-node ./src/index.js" 
 }

}
```

```bash
npm start
# Ski Day Counter
# ==============
# ... the rest of the goodies from console.log!
```

##### 1. Build your first reducer - the **goal** reducer
Pure functions that are designed to manage specific parts of your state object 

```javascript
// initialState.json - a snaptshot of what state could look at any minute
```

- Create a reducer to manage every key in the file. The reducer function will be named exactly the same thing as the key. 

```javascript
// index.js
import C from './constants'
import {goal} from './store/reducers'

// initial state of the goal reducer
// use const to prevent this value from mutating - because we are going
// to produce a new state value from the give state
const state = 10

// Actions are at minimum objects with a type field
// Action also needs to contain any information that's requried to make the change - specifically we need a new goal value - a new payload field
// So the below function describes a state mutation, where we change to goal from whatever its current value to 15
const action = {
    type: C.Set_GOAL,
    payload: 15
}

// now let's use the reducer to get the new value
const nextState = goal(state, action)
// so we are expecting the nextState to be 15
console.log(`
    initial goal: ${state}
    action: ${JSON.stringify(action)}
    new goal: ${nextState}
`)
```

Let's code the **goal reducer**
**src/store**

```javascript
// reducers.js
import C from '../constants'

function goal(state, action) {
    /*
        If the actions equals constants then return the new goal found in action.payload
        If the action type is not the goal, return the original state
    */
    if (action.type == C.SET_GOAL) {
        return action.payload
    } else {
        return state
    }
}
```

Let's use ES6 syntax:

```javascript
// reducers.js
import C from '../constants'
// make this externally available
// make this unchangeable
// set default parameters
export const goal = (state=10, action) => {
    if (action.type == C.SET_GOAL) {
        // always save goals as numbers
        return parseInt(action.payload)
    } else {
        return state
    }
}
```

##### 2. Create object reducers - build **skiDay** reducer









