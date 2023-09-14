

Pod::Spec.new do |spec|

  spec.name         = "VisxSDK"
  spec.version      = "4.1.1"
  spec.summary      = "VIS.X SDK® enables publishers access to VIS.X’s high-impact programmatic advertising on their in-app inventory."
  spec.description  = "VIS.X® is a new and unique kind of advertising technology that enables efficient execution of media and high-impact ad products at scale. VIS.X® wraps the inventory in a holistic auction offering all available products in one transaction to buyers, consequently optimizing the bidstream. YOC has developed this platform to unlock the real value of digital advertising – making VIS.X® the go-to-platform for high-impact programmatic advertising."
  spec.homepage     = "https://yoc.com"
  spec.license      = { :type => "Copyright", :text => "Copyright YOC AG. All rights reserved." }
  spec.author       = { "Yoc AG" => "sdk@yoc.com" }
  spec.platform     = :ios, "13.0"
  spec.source       = { :path => "/Users/yourUserName/Desktop/SomeFolder" }
  spec.vendored_frameworks = "VisxSDK.xcframework"
  
  spec.preserve_paths = "VisxSDK.xcframework"
  spec.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
  spec.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
  
end
