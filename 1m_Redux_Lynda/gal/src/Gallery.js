import React, {Component} from 'react'
import {connect} from 'react-redux'
import {bindActionCreators} from 'redux'

import * as GalleryActions from './actions.js'

export class Gallery extends Component {
    render() {
        console.log('props: ', this.props)
        const {images, selectedImage, selectImage} = this.props
        return(
            <div className="image-gallery">
                <div className="gallery-image">
                    <div>
                        <img src={selectedImage} />
                    </div>
                </div>
                <div className="image-scroller">
                    {images.map((image, index) => (
                        <div key={index}
                             onClick={() => selectImage(image)}>
                            <img src={image}/>
                        </div>
                    ))}
                </div>
            </div>
        )
    }
}

function mapStateToProps(state) {
    // takes the current state and assigns it to properties of component
    // It is then connected to the store and passed as this.props to Gallery
    return {
        images: state.images,
        selectedImage: state.selectedImage
    }
}

function mapActionCreatorsToProps(dispatch) {
    // the props now receive the selectImage method and not dispatch
    return bindActionCreators(GalleryActions, dispatch)
}

export default connect(mapStateToProps, mapActionCreatorsToProps)(Gallery)