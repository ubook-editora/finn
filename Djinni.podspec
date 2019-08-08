Pod::Spec.new do |s|
    s.name             = 'Djinni'
    s.version          = '4.0.0'
    s.summary          = 'A short description of Djinni-iOS.'
  
  # This description is used to generate tags and improve search results.
  #   * Think: What does it do? Why did you write it? What is the focus?
  #   * Try to keep it short, snappy and to the point.
  #   * Write the description between the DESC delimiters below.
  #   * Finally, don't worry about the indent, CocoaPods strips it!
  
    s.description      = <<-DESC
  TODO: Add long description of the pod here.
                         DESC
    s.homepage         = 'https://github.com/hiennguyenle/djinni'
    s.license          = { :type => 'MIT', :file => 'LICENSE' }
    s.author           = { 'Hien Nguyen' => 'nlhien@fossil.com' }
    s.source           = { :git => 'https://github.com/hiennguyenle/djinni.git', :tag => s.version.to_s}
  
    s.pod_target_xcconfig = {
      'DEFINES_MODULE' => 'YES',
      'GCC_WARN_INHIBIT_ALL_WARNINGS' => 'YES',
      'CLANG_CXX_LANGUAGE_STANDARD' => 'c++17',
      'USER_HEADER_SEARCH_PATHS' => '${PODS_TARGET_SRCROOT}/support-lib/**',
    }
  
    s.module_name = 'Djinni'
    
    s.ios.deployment_target = '9.0'
    s.osx.deployment_target = '10.13'
  
    s.requires_arc = true
    s.libraries = 'stdc++'

    s.source_files         = [
        'support-lib/proxy_cache_impl.hpp', 
        'support-lib/proxy_cache_interface.hpp',
        'support-lib/objc/*.{h,mm}'
      ]
    s.private_header_files = [
        'support-lib/proxy_cache_impl.hpp', 
        'support-lib/proxy_cache_interface.hpp',
        'support-lib/objc/*.h']
  end
  