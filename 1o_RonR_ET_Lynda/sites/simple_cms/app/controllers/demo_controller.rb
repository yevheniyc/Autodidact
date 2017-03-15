class DemoController < ApplicationController

  layout false

  def index
      render('index')
  end

  def hello
    render('hello')
  end


end
