import {fetchImages} from './flickr'
import {put, take, fork} from 'redux-saga/effects';

export function* loadImages() {
    const images = yield fetchImages()
    console.log('images after fetch images: ', images)
    // the put acts as dispatcher and activates a reducer
    yield put({type: 'IMAGES_LOADED', images})
    yield put({type: 'IMAGE_SELECTED', image: images[0]})
}

export function* watchForLoadImages() {
    while(true) {
        // take listens for actions of a given type and when they 
        //+ occur, it advances the saga to the next yield
        yield take('LOAD_IMAGES') // wait till action is dispatched
        // yield loadImages() instead:
        yield fork(loadImages) // to run multiple load images at a time
    }
}