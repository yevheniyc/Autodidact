const API_ENDPOINT = `https://jsonplaceholder.typicode.com/photos`;

export const fetchImages = () => {
    fetch(API_ENDPOINT).then((response) => {
        return response.json().then((json) => {
            json = json.slice(0, 10) // look at 10 images only
            const images = json.map(({albumId, id, title, url, thumbnailUrl}) => {
                return thumbnailUrl
            })
            console.log('images: ', images)
            return images
        })
    })
}