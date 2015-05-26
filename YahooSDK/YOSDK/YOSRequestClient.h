//
//  YOSRequestClient.h
//  YOSSocial
//
//  Created by Zach Graves on 2/19/09.
//  Copyright 2014 Yahoo Inc.
//  
//  The copyrights embodied in the content of this file are licensed under the BSD (revised) open source license.
//

#import <Foundation/Foundation.h>
#import "YOAuthConsumer.h"
#import "YOAuthToken.h"
#import "YOAuthRequest.h"
#import "YOSResponseData.h"

@protocol YOSRequestDelegate;

/**
 * A basic URL request manager that handles OAuth and request flow.
 */
@interface YOSRequestClient : NSObject {
@public
	/**
	 * Returns the reciever's OAuth consumer.
	 */
	YOAuthConsumer		*consumer;
	
	/**
	 * Returns the reciever's optional OAuth token.
	 */
	YOAuthToken			*token;
	
	/**
	 * Returns the receiver’s HTTP request method.
	 */
	NSString			*HTTPMethod;
	
	/**
	 * Returns the reciever's request URL.
	 */
	NSURL				*requestUrl;
	
	/**
	 * Returns the reciever's request parameters.
	 */
	NSMutableDictionary	*requestParameters;
	
	/**
	 * Returns the reciever's request headers.
	 */
	NSMutableDictionary	*requestHeaders;
	
	/**
	 * Returns the receiver's HTTP body data.
	 */
	NSData				*HTTPBody;
	
	/**
	 * Returns the location of the signed OAuth parameters in the request. 
	 */
	NSString			*oauthParamsLocation;
	
	/**
	 * Returns the timeout interval for the request, in seconds.
	 */
	NSTimeInterval		timeoutInterval;

@private
	/**
	 * Returns the custom user-agent for this request.
	 */
	NSString			*userAgentHeaderValue;
	
	/**
	 * Returns the delegate for all asynchronous requests.
	 */
	id<YOSRequestDelegate>	requestDelegate;
	
	/**
	 * Returns the URLResponse from an asychronous request.
	 */
	NSURLResponse		*response;
	
	/**
	 * Returns the incoming data from an asychronous request.
	 */
    NSMutableData		*responseData;
	
	/**
	 * Returns the URLConnection from an asychronous request.
	 */
	NSURLConnection		*URLConnection;
	
}

@property (nonatomic, readwrite, strong) YOAuthConsumer *consumer;
@property (nonatomic, readwrite, strong) YOAuthToken *token;
@property (nonatomic, readwrite, strong) NSString *HTTPMethod;
@property (nonatomic, readwrite, strong) NSURL *requestUrl;
@property (nonatomic, readwrite, strong) NSMutableDictionary *requestParameters;
@property (nonatomic, readwrite, strong) NSMutableDictionary *requestHeaders;
@property (nonatomic, readwrite, strong) NSData *HTTPBody;
@property (nonatomic, readwrite, strong) NSString *oauthParamsLocation;
@property (nonatomic, readwrite) NSTimeInterval timeoutInterval;
@property (nonatomic, readwrite, strong) NSString *userAgentHeaderValue;

@property (nonatomic, readwrite, strong) id<YOSRequestDelegate> requestDelegate;
@property (nonatomic, readwrite, strong) NSURLResponse *response;
@property (nonatomic, readwrite, strong) NSMutableData *responseData;
@property (nonatomic, readwrite, strong) NSURLConnection *URLConnection;

/**
 * Returns a request object for the specified OAuth consumer and (optional) token.
 * @return			The initialized request client.
 */
- (instancetype)initWithConsumer:(YOAuthConsumer *)aConsumer andToken:(YOAuthToken *)aToken;

/**
 * Returns the response data for the request through a synchronous connection.
 * @return			A YOSResponseData object containing all the available response data.
 */
- (YOSResponseData *)sendSynchronousRequest;

/**
 * Sends the request asynchronously with the provided delegate object.
 * @return			A boolean determining if the request was successful. 
 */
- (BOOL)sendAsyncRequestWithDelegate:(id)delegate;

/**
 * Returns a prepared YOAuthRequest object.
 * @private
 * @return			A prepared YOAuthRequest object containing all parameters provided and those generated by the signature process.
 */
- (YOAuthRequest *)buildOAuthRequest;

/**
 * Returns a prepared NSMutableURLRequest object.
 */
- (NSMutableURLRequest *)buildUrlRequest;

/**
 * Returns a string for the User-Agent header of the URLRequest.
 * @private
 * @return			A NSString containing a custom User-Agent detailing the SDK name and version, generic device/system information and locale.
 */
- (NSString *)buildUserAgentHeaderValue;

/**
 * Cancels the request.
 */
- (void)cancel;

@end

/**
 * The protocol for all request delegates.
 */
@protocol YOSRequestDelegate <NSObject>

@optional

/**
 * Called just before the request is sent to the server.
 */
- (void)request:(YOSRequestClient *)request didReceiveResponse:(NSURLResponse *)request;

/**
 * Called when the server responds and begins to send back data.
 */
- (void)request:(YOSRequestClient *)request didReceiveData:(NSData *)response;

/**
 * Called when an error prevents the request from completing successfully.
 */
- (void)requestDidFailWithError:(YOSResponseData *)error request:(YOSRequestClient *)request;

/**
 * Called when a request returns a response.
 */
- (void)requestDidFinishLoading:(YOSResponseData *)result request:(YOSRequestClient *)request;

/**
 * Called when the request was cancelled.
 */
- (void)connectionWasCancelled;

@end
