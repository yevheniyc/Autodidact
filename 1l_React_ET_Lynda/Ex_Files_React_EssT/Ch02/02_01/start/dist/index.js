// 0. Declare for simplicity
const {createElement} = React
const {render} = ReactDOM

// Use JSX - XML-style rendering
render(
	<h1 id='title'
		className='header'
		style={{backgroundColor: 'orange', color: 'white', fontFamily: 'verdana'}}>
	Hellow World
	</h1>,
	document.getElementById('react-container')
)