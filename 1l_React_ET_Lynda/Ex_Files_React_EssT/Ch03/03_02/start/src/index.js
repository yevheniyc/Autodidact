import React from 'react'
import { render } from 'react-dom'
import {SkiDayCount} from './components/SkiDayCount'

window.React = React // sometimes an error: React is not defined shows up, this will resolve it

render(
	<SkiDayCount />,
	document.getElementById('react-container')
)