Pod::Spec.new do |s|
    s.name             = 'Djinni'
    s.version          = '4.4.1'
    s.summary          = 'Djinni is a tool for generating cross-language type declarations and interface bindings.'
    s.description      = <<-DESC
    Djinni is a tool for generating cross-language type declarations and interface bindings.
    It's designed to connect C++ with either Java or Objective-C. Python support is experimental. 
    For more information see README.Python.md
                           DESC
    s.homepage         = 'https://github.com/hiennguyenle/djinni'
    
    s.license          = { :type => 'MIT' }
    
    s.author           = { 'Hien Nguyen' => 'hien.nguyenle.it@gmail.com' }
    
    s.source           = { :git => 'https://github.com/hiennguyenle/djinni.git', :tag => "#{s.version}" }
    
    s.module_name = 'Djinni'
    s.requires_arc = true
    s.library = 'c++'
    
    s.default_subspec = 'objc'
    s.ios.deployment_target  = '9.0'
    s.osx.deployment_target  = '10.10'

    s.subspec 'objc' do |ss|
        ss.pod_target_xcconfig = {
            'HEADER_SEARCH_PATHS' => [
                'support-lib/objc'
            ],
            'USER_HEADER_SEARCH_PATHS' => [
                'support-lib/extension/json/nlohmann'
            ]
        }
        ss.source_files         = [
            "support-lib/extension/json/nlohmann/json.hpp",
            "support-lib/extension/json/objc/DJIMarshal+Json.h",
            "support-lib/objc/DJICppWrapperCache+Private.h",
            "support-lib/objc/DJIError.h",
            "support-lib/objc/DJIError.mm",
            "support-lib/objc/DJIMarshal+Private.h",
            "support-lib/objc/DJIObjcWrapperCache+Private.h",
            "support-lib/objc/DJIProxyCaches.mm",
            "support-lib/proxy_cache_impl.hpp",
            "support-lib/proxy_cache_interface.hpp",
        ]
    end
end
