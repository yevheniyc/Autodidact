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

***

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

***
#### Egghead Intervention

##### 1. Simple Redux app
Let's create a simple redux application

```javascript
// the reducer; if state === 'underfinded' then initialize to 0,
    // otherwise uses the current getState() result
// the action - which is defined as {type: 'something'}
const counter = (state = 0, action) => {
    switch (action.type) {
        case 'INCREMENT':
            return state + 1
        case 'DECREMENT':
            return state - 1
        default:
            return state
    }
}

const {createStore} = Redux // import {createStore} from 'redux' if with npm
const store = createStore(counter) // holds the state tree of the application

const render = () => {
    document.body.innerText = store.getState()
}

// adds the change listener - called any time an action is dispatched
store.subscribe(render)
// // call the initial render() to show default state on page
render()

// everytime I click anywhere in the document, 
    // call the counter reducer to update the state
    // call the render subscriber to update the page
document.addEventListener('click', () => {
    store.dispatch({type: 'INCREMENT'})
});
```

##### 2. Reimplement the **createStore** provided by Redux
- Implement the createStore from scratch

```javascript

const counter = (state = 0, action) => {
    switch (action.type) {
        case 'INCREMENT':
            return state + 1
        case 'DECREMENT':
            return state - 1
        default:
            return state
    }
}

// let's reimplement createStore from scratch
const createStore = (reducer) => {
    let state // define state variable
    let listener [] // because subscribe can be called multiple times
                    // we need to keep track of the listeners

    const getState = () => state

    const dispatch = (action) => {
        // the only way to keep track of the internal state
        state = reducer(state, action)
        listeners.forEach(listener => listener())
    }

    const subscribe = (listener) => {
        // subscribe just adds listeners (fucntions) to a global counter
        // on dispatch, these listeners are executed
        listeners.push(listener);
        // the return value is a function that includes a list of listeners
        // excpet the one passed to subscribe
        return () => {
            // so far we didn't provide a way to unsubscribe a method
            // so instead, we will return a function when subscirbe is called
                // that will return all listeners, except the one called here
            listners = listeners.filter(l => l !== listener)
        }
    }

    dispatch({}) // get the reducer to populate the initial state

    return {getState, dispatch, subscribe} // redux store
}


const store = createStore(counter) // holds the state tree of the application

const render = () => {
    document.body.innerText = store.getState()
}

// adds the change listener - called any time an action is dispatched
store.subscribe(render)
// call the initial render() to show default state on page
render()


document.addEventListener('click', () => {
    store.dispatch({type: 'INCREMENT'})
});
```

##### 3. Let's add React to the mix

```html
<script src="redux"></script>
<script src="react"></script>
<body>
    <div id='root'></div>
</body>
```

```javascript
const counter = (state = 0, action) => {
    switch (action.type) {
        case 'INCREMENT':
            return state + 1
        case 'DECREMENT':
            return state - 1
        default:
            return state
    }
}

// how the current application state converts into renderable output
// howt the callbacks are bound to the event handlers
const Counter = ({value}) => (
    <h1>{value}</h1>
    <button onClick={onIncrement}>+</button>
    <button onClick={onDecrement}>-</button>
)

const {createStore} = Redux; // import {createStore} from 'redux'
const store = createStore(counter) // holds the state tree of the application

const render = () => {
    ReactDOM.render(
        // Counter's value should be taken from the Redux store's current state
        // when onIncrement or onDecrement are triggered, then dispatch the approriate action
        //+ and update the current state of the application
        <Counter value={store.getState()}
            onIncrement={() =>
                store.dispatch({
                    type: 'INCREAMENT'
                })
            }
            onDecrement={() =>
                store.dispatch({
                    type: 'DECREMENT'
                })
        }/>,
        document.getElementById('root')
    )
}

// the render function is executed any time the state changes and the action is called
store.subscribe(render)
render()
```

##### 4. Let't avoid array mutation with **expect** and **deep-freeze** libraries
Learn how to manage states without mutatting the original state, and using expect for testing, and deep-freeze for testing for mutability.
**Expect** - used for testing
**Deep-Freeze** - used to make sure that the code is free from mutations

```html
<script src="expect"></script>
<script src="deep-freeze"></script>
```

```javascript

/* adding a number to a list without mutation */
const addCounter = (list) => {
    // add a new item at the end of the array, mutating the array
    list.push(0)
    return list
}

const addCounter = (list) => {
    // add 0 to list, without mutating the list
    return list.concat([0])
        // or use ES6 spread operator
    return [...list, 0]
}

/* remove an item from a list at an index, without array mutation */
const removeCounter = (list, index) => {
    list.splice(index, 1) // remove one element at index position
    return list // return mutated list
        // or without mutation
    return list
        // take the first part of the array up to index position
        .slice(0, index)
        // to the first part of the array concat the second part from 
        //+ index + 1 position, omitting the alement at index position
        .concat(list.slice(index + 1))
        
        // or with ES6 syntax without mutation
    return [
        ...list.slice(0, index), // take only the first part of the list till index position
        ...list.slice(index + 1) // add the second part from index + 1 postion
    ]
}

/* increment a counter at a specified position */
const incrementCounter = (list, index) => {
    list[index]++
    return list // return mutated list
        // or without mutation
    return list
        .slice(0, index) // get the copy of the first part of the array
        .concat([list[index] + 1]) // add and increment the item at position = index
        .contat(list.slice(index + 1)) // add a copy of the second part of the array

        // or ES6 without mutation
    return [
        ...list.slice(0, index),
        list[index] + 1, // specify the new item
        ...list.slice(index + 1)
    ]
}

const testAddCounter = () => {
    // appends a zero at the end of an array
    const listBefore = []
    const listAfter = [0]

    // we need to learn to avoid mutations in redux
    deepFreeze(listBefore)

    expect(
        addCounter(listBefore)
    ).toEqual(listAfter)
}

const testRemoveCounter = () => {
    // remove an item from indicated position
    const listBefore = [0, 10, 20]
    const listAfter = [0, 20] // removed at position 1

    deepFreeze(listBefore)

    expect(
        removeCounter(listBefore, 1)
    ).toEqual(listAfter)
}

const testIncrementCounter = () => {
    listBefore = [0, 10, 20]
    listAfter = [0, 11, 20]

    deepFreeze(listBefore)

    expect(
        incrementCounter(listBefore, 1)
    ).toEqual(listAfter)
}

testAddCounter();
testRemoveCounter();
console.log('All tests passed.')
```

##### 5. Avoiding Object Mutation with **Object.assign()** and ...spread
To use test assertions as before use **expect** and **deep-freeze**
```html
<script src="expect"></script>
<script src="deep-freeze"></script>
```

```javascript
// toggle ToDo
const toggleToDo = (todo) => {
    todo.completed = !todo.completed
    return todo // this will mutate the original object
        // or without mutating the origianl object
        // the drawback is that i have to remember to update 
        //+ this object every time todo properties are added/removed
    return {
        id: todo.id,
        text: todo.text,
        completed: !todo.completed
    }
        // or ES6 without mutation and irrelavence to changes to todo object
    return Object.assign({}, todo, {
        completed: !todo.completed
    })
        // or a newer way - which i don't think is implemented yet
    return {
        ...todo,
        completed: !todo.completed
    }
}

const testToggleToDo = () => {
    const todoBefore = {
        id: 0,
        text: 'Learn Redux',
        completed: false
    }

    const todoAfter = {
        id: 0,
        text: 'Learn Redux',
        completed: true
    }

    deepFreeze(todoBefore)

    expect(
        toggleTodo(todoBefore)
    ).toEqual(todoAfter)
}
```

##### 6. Writing a Todo List Reducer (Adding a Todo, Toggling a Todo)
To use test assertions as before use **expect** and **deep-freeze**
```html
<script src="expect"></script>
<script src="deep-freeze"></script>
```

```javascript
// state = an array of todos
// reducer = is a pure function that contains an update logic for your
//+ application => that is, how the next state is calculated given the 
//+ the current state and the action being dispatched
const todos = (state = [], action) => {
    switch (action.type) {
        case 'ADD_TODO':
            return [
                ...state,
                {
                    id: action.id,
                    text: action.text,
                    completed: false
                }
            ]
        case 'TOGGLE_TODO':
            // produce a new array with the map method
            return state.map(todo => {
                if (todo.id !== action.id) {
                    return todo
                }

                return {
                    ...todo, 
                    completed: !todo.completed
                }
            }) 
        default:
            return state
    }
}

// before writing a reducer, we need to know if it's code is correct, 
//+ by writing a test for it
const testAddTodo = () => {
    const stateBefore = []
    const action = {
        type: 'ADD_TODO',
        id: 0,
        text: 'Learn Redux'
    }
    const stateAfter = {
        id: 0, // has the same id as the action object
        text: 'Learn Redux',
        completed: false
    }

    // make sure the reducer is a pure function
    deepFreeze(stateBefore)
    deepFreeze(action)

    expect(
        todos(stateBefore, action)
    ).toEqual(stateAfter) // deeply equal

    testAddTodo();
    // unless an exception been raised, show the success message
    console.log('All tests passed.')
}

const testToggleTodo = () => {
    const stateBefore = [
        {
            id: 0,
            text: 'Learn Redux',
            completed: false
        }, 
        {
            id: 1,
            text: 'Go shopping',
            completed: false
        }
    ]
    const action = {
        type: 'TOGGLE_TODO',
        id: 1
    }
    const stateAfter = [
        {
            id: 0,
            text: 'Learn Redux',
            completed: false
        }, 
        {
            id: 1,
            text: 'Go shopping',
            completed: true
        }
    ]

    deepFreeze(stateBefore)
    deepFreeze(action)

    expect(
        todos(state, action)
    ).toEqual(stateAfter)
}

testAddTodo()
testToggleTodo()
consle.log('All tests passed.')
```

##### 7. Reducer Composition with Arrays
To use test assertions as before use **expect** and **deep-freeze**
```html
<script src="expect"></script>
<script src="deep-freeze"></script>
```

```javascript
const todo = (state, action) => {
    switch (action.type) {
        case 'ADD_TODO':
            return {
                id: action.id,
                text: action.text,
                completed: false
            }
        case 'TOGGLE_TODO': 
            if (state.id !== action.id) {
                return state
            }

            return {
                ...state, 
                completed: !state.completed
            }
        default:
            return state
    }
}

const todos = (state = [], action) => {
    switch (action.type) {
        case 'ADD_TODO':
            return [
                ...state,
                todo(undefined, action)
            ]
        case 'TOGGLE_TODO':
            // call the todo reducer for each state
            return state.map(t => todo(t, action)) 
        default:
            return state
    }
}

// before writing a reducer, we need to know if it's code is correct, 
//+ by writing a test for it
const testAddTodo = () => {
    const stateBefore = []
    const action = {
        type: 'ADD_TODO',
        id: 0,
        text: 'Learn Redux'
    }
    const stateAfter = {
        id: 0, // has the same id as the action object
        text: 'Learn Redux',
        completed: false
    }

    // make sure the reducer is a pure function
    deepFreeze(stateBefore)
    deepFreeze(action)

    expect(
        todos(stateBefore, action)
    ).toEqual(stateAfter) // deeply equal

    testAddTodo();
    // unless an exception been raised, show the success message
    console.log('All tests passed.')
}

const testToggleTodo = () => {
    const stateBefore = [
        {
            id: 0,
            text: 'Learn Redux',
            completed: false
        }, 
        {
            id: 1,
            text: 'Go shopping',
            completed: false
        }
    ]
    const action = {
        type: 'TOGGLE_TODO',
        id: 1
    }
    const stateAfter = [
        {
            id: 0,
            text: 'Learn Redux',
            completed: false
        }, 
        {
            id: 1,
            text: 'Go shopping',
            completed: true
        }
    ]

    deepFreeze(stateBefore)
    deepFreeze(action)

    expect(
        todos(state, action)
    ).toEqual(stateAfter)
}

testAddTodo()
testToggleTodo()
consle.log('All tests passed.')
```

##### 8. Reducer Composition with objects
The actions of multiple reducers that have been combine into a single reducer are handled independently
```html
<script src="expect"></script>
<script src="deep-freeze"></script>
```

```javascript
const todo = (state, action) => {
    switch (action.type) {
        case 'ADD_TODO':
            return {
                id: action.id,
                text: action.text,
                completed: false
            }
        case 'TOGGLE_TODO': 
            if (state.id !== action.id) {
                return state
            }

            return {
                ...state, 
                completed: !state.completed
            }
        default:
            return state
    }
}

const todos = (state = [], action) => {
    switch (action.type) {
        case 'ADD_TODO':
            return [
                ...state,
                todo(undefined, action)
            ]
        case 'TOGGLE_TODO':
            // call the todo reducer for each state
            return state.map(t => todo(t, action)) 
        default:
            return state
    }
}

// let's write another reducer
const visibilityFilter = (
    state = 'SHOW_ALL',
    action
) => {
    switch (action.type) {
        case 'SET_VISIBILITY_FILTER':
            return action.filter
        default:
            return state
    }
}

// to store this information, I don't need to change the existing reducer,
//+ but instead we will use a reducer composition patterns and create a new reducer
//+ that calls the existing reducer to manage parts of its state and combine their
//+ results in a single state object 
const todoApp = (state = {}, action) => {
    return {
        todos: todos(
            state.todos,
            action
        ),
        visibilityFilter: visibilityFilter(
            state.visibilityFilter,
            action
        )
    }
}

// !IMPORTANT: to simplify the above, Redux implements combineReducers()
const {combineReducers} = Redux
const todoApp = combineReducers({
    todos: todo, // ES6 object-literal allows for: todos, visibilityFilter
    visibilityFilter: visibilityFilter
})

const {createStore} = Redux; // import {createStore} from 'redux'
const store = createStore(todoApp)

console.log('Dispatch SET_VISIBILITY_FILTER')
store.dispatch({
    type: 'SET_VISIBILITY_FILTER',
    filter: 'SHOW_COMPLETED'
})

// Tests as specified above
```

***

##### 2. Create object reducers - build **skiDay** reducer









