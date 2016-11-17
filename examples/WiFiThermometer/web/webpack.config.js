"use strict";

var path = require("path");
var webpack = require("webpack");
var ExtractTextPlugin = require("extract-text-webpack-plugin");

module.exports = {
    context: path.resolve("./src"),
    entry: "./index.js",
    alias: {
        "normalize.css": path.resolve("./node_modules/normalize.css/normalize.css")
    },
    output: {
        path: path.resolve("./assets"),
        publicPath: "/assets",
        filename: "all-in-one.js"
    },
    devServer: {
        contentBase: path.resolve("./")
    },
    module: {
        loaders: [
            {
                test: /\.js$/,
                exclude: /(node_modules|bower_components)/,
                loaders: [ "babel-loader" ]
            },
            {
                test: /\.css/,
                loader: ExtractTextPlugin.extract("style-loader", "css-loader")
            },
            {
                test: /\.less$/,
                loader: ExtractTextPlugin.extract("style-loader", "css-loader!less-loader")
            }
        ]
    },
    plugins: [
        new ExtractTextPlugin("./stylesheet.css"),
        new webpack.ProvidePlugin({
            "$": "jquery",
            "jQuery": "jquery"
        })
    ]
};
