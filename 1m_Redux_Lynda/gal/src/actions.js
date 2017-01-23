export const IMAGE_SELECTED = 'IMAGE_SELECTED'
const LOAD_IMAGES = 'LOAD_IMAGES'

export function selectImage(image) {
    return {
        type: IMAGE_SELECTED,
        image
    }
}

export function loadImages() {
    return {
        type: LOAD_IMAGES
    }
}