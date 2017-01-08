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