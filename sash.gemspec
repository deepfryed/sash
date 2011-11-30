Gem::Specification.new do |s|
  s.name              = "sash"
  s.version           = "0.1.1"
  s.date              = "2011-12-01"
  s.authors           = "Bharanee Rathna"
  s.email             = "deepfryed@gmail.com"
  s.summary           = "compute a compact base64 string hash"
  s.description       = "computes a 64bit hash using sdbm hash function and outputs a compact string representation"
  s.homepage          = "http://github.com/deepfryed/sash"
  s.files             = Dir["ext/**/*.{c,rb}"] + %w(README.rdoc) + Dir["test/*.rb"]
  s.extra_rdoc_files  = %w(README.rdoc)
  s.extensions        = %w(ext/extconf.rb)
  s.require_paths     = %w(lib)
end
