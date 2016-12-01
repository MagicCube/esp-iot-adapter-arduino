"use strict";

var path = require("path");
var webpack = require("webpack");
var ExtractTextPlugin = require("extract-text-webpack-plugin");
var HtmlWebpackPlugin = require("html-webpack-plugin");
var HtmlWebpackInlineSourcePlugin = require("html-webpack-inline-source-plugin");

module.exports = {
    context: path.resolve("./src"),
    entry: "./index.js",
    alias: {
        "normalize.css": path.resolve("./node_modules/normalize.css/normalize.css")
    },
    output: {
        path: path.resolve("./dist"),
        publicPath: "/",
        filename: "index.js"
    },
    devServer: {
        contentBase: path.resolve("./")
    },
    module: {
        loaders: [
            {
                test: /\.js$/,
                exclude: /(node_modules|bower_components)/,
                loader: "babel-loader"
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
        new ExtractTextPlugin("index.css"),
        new HtmlWebpackPlugin({
            filename: "index.html",
            template: "index.html",
            inlineSource: ".(js|css)$",
            minify: {
                removeAttributeQuotes: true,
                collapseWhitespace: true
            }
        }),
        new HtmlWebpackInlineSourcePlugin()
    ]
};
