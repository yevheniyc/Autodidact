import { Component } from 'react'
import { SkiDayList } from './SkiDayList'
import { SkiDayCount } from './SkiDayCount'

export class App extends Component {
	// The constructor initiation ensures that this.state is excesible inside methods
	constructor (props) {
		super(props)		// call the super class and pass props to it
		this.state = {
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
	}
	countDays(filter) {
		const { allSkiDays } = this.state
		return allSkiDays.filter(
			(day) => (filter) ? day[filter] : day).length
	}
	render() {
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
}




