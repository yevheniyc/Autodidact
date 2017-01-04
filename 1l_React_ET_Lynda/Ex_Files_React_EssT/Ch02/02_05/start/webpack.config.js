var webpack = require("webpack");

module.exports = {
    // entry point == the file where it all begins
    entry: "./src/index.js",
    // specify the assets files and the bundled output location
    output: {
        path: "dist/assets",    // where all of the unbundled asset files reside
        filename: "bundle.js",  // the output filename
        publicPath: "assets"    // folder name where all of the bundled files will reside
    },
    // another important feature when working with webpack is to setup a devServer, which
    // works similary to httpster, however, it allows for hot reloads
    devServer: {
        inline: true,
        contentBase: '/.dist', // where the files are located
        port: 3000
    },
    module: {
        // specify loaders - different tasks that we want webpack to perform
        loaders: [
            { // the first step of the task we are going to setup is the Babel loader
                // 1. Look at all of the files that have .js extension
                test: /\.js$/,              
                // 2. Exclude anything that we don't want Babel to touch
                exclude: /(node_modules)/,
                // 3. The name of the loader to use
                loader: ['babel-loader'],
                // 4. Just like in .babelrc file, specify presets we will use
                query: {
                    presets: ["latest", "react", "stage-0"]
                }
            }
        ]
    }
}