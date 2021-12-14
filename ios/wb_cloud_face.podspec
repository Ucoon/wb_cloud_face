#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html.
# Run `pod lib lint wb_cloud_face.podspec` to validate before publishing.
#
Pod::Spec.new do |s|
  s.name             = 'wb_cloud_face'
  s.version          = '0.0.1'
  s.summary          = '腾讯云人脸核身'
  s.description      = <<-DESC
腾讯云人脸核身
                       DESC
  s.homepage         = 'http://example.com'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'ucoon' => 'ucoontech@gmail.com' }
  s.source           = { :path => '.' }
  s.source_files = 'Classes/**/*'
  s.public_header_files = 'Classes/**/*.h'
    # 腾讯人脸核身SDk
  s.vendored_frameworks = 'Framework/Libs/WBCloudReflectionFaceVerify.framework', 'Framework/Libs/YTCommonLiveness.framework', 'Framework/Libs/YTFaceTrackerLiveness.framework', 'Framework/Libs/YTFaceAlignmentTinyLiveness.framework', 'Framework/Libs/YTPoseDetector.framework', 'Framework/Libs/YTFaceDetectorLiveness.framework', 'Framework/Libs/YTFaceLiveReflect.framework', 'Framework/Libs/tnnliveness.framework', 'Framework/Libs/TuringShieldCamRisk.framework'
  s.resource = 'Framework/Resources/face-tracker-v001.bundle', 'Framework/Resources/WBCloudReflectionFaceVerify.bundle'
  s.dependency 'Flutter'
  s.platform = :ios, '8.0'

  # Flutter.framework does not contain a i386 slice.
  s.pod_target_xcconfig = { 'DEFINES_MODULE' => 'YES', 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'i386' }
end
