const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');

const outputDir = path.join(__dirname, "dist");
console.log(outputDir)
module.exports = {
  entry: './src/Index.bs.js',
  output: {
    path: path.join(outputDir),
    publicPath: '/',
    filename: 'index.js',
  },
  module: {
    rules: [
      { test: /\.js$/, exclude: /node_modules/, loader: "babel-loader" },
    ]
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: "public/index.html"
    }),
  ],
  devServer: {
    compress: true,
    contentBase: path.join(__dirname, "public"),
    port: process.env.PORT || 9000,
    historyApiFallback: true
  }
};
