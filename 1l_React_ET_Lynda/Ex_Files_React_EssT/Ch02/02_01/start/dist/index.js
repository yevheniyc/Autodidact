// 0. Declare for simplicity
const {createElement} = React
const {render} = ReactDOM

const style = {
	backgroundColor: 'orange',
	color: 'white',
	fontFamily: 'verdana'
}

// 1. Create elements
const title = createElement(
	'h1',
	{id: 'title', className: 'header', style: style},
	'Hello World'
)

// 2. Render elements in the dom
render(
	title,
	document.getElementById('react-container')
)