import { Component } from 'react'
import fetch from 'isomorphic-fetch' // loading the data from API!
import Member from './Member'

class MemberList extends Component {

    constructor(props) {
        super(props)
        this.state = {
            members: [],
            loading: false // 
        }
    }

    // will fire as soon the as the render method fires for the first time
    componentDidMount() {
        this.setState({loading: true})
        fetch('https://api.randomuser.me/?nat=US&results=12')
            // once we receive a response from the API, we will trun it into json
            // function(response) {
                // return response.json()
            // } -> same as below
            .then(response => response.json())
            // let's pass the return parameter (response.json() as json into the next function)
            .then(json => json.results)
            // take results to set the state
            .then(members => this.setState({
                members, // same as members = members -> ES6 literal enhancement
                loading: false
            }))
    }

    render() {
    	const { members, loading } = this.state
        return (
            <div className="member-list">
                <h1>Society Members</h1>

                { 
                    (loading) ? 
                    <span>laoding...</span> :
                    <span>{members.length} members</span>
                }
                { 
                    (members.length) ? 
                        members.map(
                            (member, i) => 
                                <Member key={i} 
                                        name={member.name.first + ' ' + member.name.last}
                                        email={member.email}
                                        thumbnail={member.picture.thumbnail}/>
                        ):
                        <span>Currently 0 Members </span>
                }
            </div>
        )
    }
}

export default MemberList