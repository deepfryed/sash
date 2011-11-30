require 'sash'
require 'minitest/spec'

describe 'sash' do
  it 'should work' do
    Sash.base64("hi, this is sash - so how was your day ?").must_equal "ixeLC8U8SC"
  end

  it 'should work with options' do
    Sash.base64("hi, this is sash - so how was your day ?", method: Sash::METHOD_DJB2).must_equal "HI6K0nlcyH9"
  end
end

MiniTest::Unit.autorun
