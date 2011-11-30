require 'sash'
require 'minitest/spec'

describe 'sash' do
  it 'should work' do
    Sash.base64("hi, this is sash - so how was your day ?").must_equal "ixeLC8U8SC"
  end
end

MiniTest::Unit.autorun
