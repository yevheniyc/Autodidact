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