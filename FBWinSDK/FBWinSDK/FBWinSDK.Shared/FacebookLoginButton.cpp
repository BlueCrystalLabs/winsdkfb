﻿//******************************************************************************
//
// Copyright (c) 2015 Microsoft Corporation. All rights reserved.
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
//******************************************************************************

#include "pch.h"
#include "FacebookLoginButton.h"
#include "FacebookSession.h"
#include "FacebookPermissions.h"

using namespace Concurrency;
using namespace Facebook;
using namespace Facebook::Graph;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;

FBLoginButton::FBLoginButton() :
//    m_loginBehavior(SessionLoginBehavior::SessionLoginBehaviorWithFallbackToWebView),
    m_permissions(nullptr)
{
    String^ styleKey = FBLoginButton::typeid->FullName;
    this->DefaultStyleKey = styleKey;
}

void FBLoginButton::OnApplyTemplate(
    )
{
    Button::OnApplyTemplate();

    // TODO: Do we need to save the token here and unregister the event handler
    // at some point?
    this->Click += ref new RoutedEventHandler(this, &FBLoginButton::OnClick);
}

// TODO: Implement behaviors.  These will have to be plumbed down into the
// Session as well.
//SessionLoginBehavior FBLoginButton::LoginBehavior::get()
//{
//    return m_loginBehavior;
//}
//
//void FBLoginButton::LoginBehavior::set(SessionLoginBehavior value)
//{
//    m_loginBehavior = value;
//}
//

FBPermissions^ FBLoginButton::Permissions::get()
{
    return m_permissions;
}

void FBLoginButton::Permissions::set(FBPermissions^ Permissions)
{
    m_permissions = Permissions;
}

void FBLoginButton::InitWithPermissions(
    FBPermissions^ Permissions
    )
{
	m_permissions = Permissions;
}

void FBLoginButton::OnClick(
    Object^ sender,
    RoutedEventArgs^ e
    )
{
    FBSession^ s = FBSession::ActiveSession;

    if (s->LoggedIn == true)
    {
        ;
    }
    else
    {
        create_task(s->LoginAsync(m_permissions))
            .then([=](FBResult^ result)
        {
            if (result->Succeeded)
            {
                FBUser^ user = static_cast<FBUser^>(result->Object);
            }
            else
            {
                ;
            }
        });
    }
}
