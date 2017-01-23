export const IMAGE_SELECTED = 'IMAGE_SELECTED'

export function selectImage(image) {
    return {
        type: IMAGE_SELECTED,
        image
    }
}