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