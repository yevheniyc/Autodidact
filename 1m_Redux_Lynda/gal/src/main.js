import "babel-polyfill"

import React from 'react'
import ReactDOM from 'react-dom'

import Gallery from './Gallery'

import {createStore, applyMiddleware} from 'redux'
import createSagaMiddleware from 'redux-saga'
import reducer from './reducer'

import {loadImages} from './sagas'

const store = createStore(
    reducer,
    // execute sayHello as a regular method, 
    // by executing next() behind the scenes
    applyMiddleware(createSagaMiddleware(loadImages))
)

import {Provider} from 'react-redux'

ReactDOM.render(
    <Provider store={store}>
        <Gallery />
    </Provider>,
    document.getElementById('root')
)